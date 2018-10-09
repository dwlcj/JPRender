#include "Camera.h"
#include "../Windows/Application.h"
#include "../Windows/Event.h"

namespace EDX
{
	Camera::Camera()
	{
		Init(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), 1024, 640, float(Math::EDX_PI_4), 1.0f, 1000.0f);
	}

	Camera::Camera(const Vector3& vPos, const Vector3& vTar, const Vector3& vUp, int iResX, int iResY, float fFOV, float fNear, float fFar)
	{
		Init(vPos, vTar, vUp, iResX, iResY, fFOV, fNear, fFar);
	}

	void Camera::Init(const Vector3& vPos, const Vector3& vTar, const Vector3& vUp, int iResX, int iResY,
		float fFOV, float fNear, float fFar)
	{
		mPos = vPos;
		mTarget = vTar;
		mUp = vUp;
		mFilmResX = iResX;
		mFilmResY = iResY;
		mFOV = fFOV;
		mNearClip = fNear;
		mFarClip = fFar;

		mMoveScaler = 1.0f;
		mRotateScaler = 0.0025f;

		mFOV_2 = mFOV / 2.0f;

		mDir = Math::Normalize(mTarget - mPos);

		mYaw = Math::Atan2(mDir.x, mDir.z);
		mPitch = -Math::Atan2(mDir.y, Math::Sqrt(mDir.x * mDir.x + mDir.z * mDir.z));

		mView = Matrix::LookAt(mPos, mTarget, mUp);
		mViewInv = Matrix::Inverse(mView);

		Resize(mFilmResX, mFilmResY);
		//mRatio = mFilmResX / float(mFilmResY);
		//mProj = Matrix::Perspective(mFOV, mRatio, mNearClip, mFarClip);
		//mScreenToRaster = Matrix::Scale(float(mFilmResX), float(mFilmResY), 1.0f) *
		//	Matrix::Scale(0.5f, -0.5f, 1.0f) *
		//	Matrix::Translate(Vector3(1.0f, -1.0f, 0.0f));
		//mRasterToCamera = Matrix::Mul(Matrix::Inverse(mProj), Matrix::Inverse(mScreenToRaster));
		//mCameraToRaster = Matrix::Inverse(mRasterToCamera);
		//mRasterToWorld = Matrix::Mul(mViewInv, mRasterToCamera);
		//mWorldToRaster = Matrix::Inverse(mRasterToWorld);

		Transform();
	}

	void Camera::Resize(int iWidth, int iHeight)
	{
		mFilmResX = iWidth;
		mFilmResY = iHeight;

		mRatio = mFilmResX / float(mFilmResY);
		mProj = Matrix::Perspective(mFOV, mRatio, mNearClip, mFarClip);
		mScreenToRaster = Matrix::Scale(float(mFilmResX), float(mFilmResY), 1.0f) *
			Matrix::Scale(0.5f, -0.5f, 1.0f) *
			Matrix::Translate(Vector3(1.0f, -1.0f, 0.0f));
		mRasterToCamera = Matrix::Mul(Matrix::Inverse(mProj), Matrix::Inverse(mScreenToRaster));
		mCameraToRaster = Matrix::Inverse(mRasterToCamera);
		mRasterToWorld = Matrix::Mul(mViewInv, mRasterToCamera);
		mWorldToRaster = Matrix::Inverse(mRasterToWorld);
	}

	void Camera::Transform()
	{
		auto KeyPressed = [](const int key)
		{
			return (GetAsyncKeyState(key) & 0x8000) != 0;
		};

		if (Application::IsThisApplicationForeground())
		{
			if (KeyPressed('W'))
				mMovementImpulse.z += 1.0f;
			if (KeyPressed('S'))
				mMovementImpulse.z -= 1.0f;
			if (KeyPressed('A'))
				mMovementImpulse.x -= 1.0f;
			if (KeyPressed('D'))
				mMovementImpulse.x += 1.0f;
			if (KeyPressed('Q'))
				mMovementImpulse.y -= 1.0f;
			if (KeyPressed('E'))
				mMovementImpulse.y += 1.0f;
		}

		const float fDeltaTime = mTimer.GetElapsedTime();
		if (Math::Length(mMovementVelocity) > 0.0f || Math::Length(mMovementImpulse) > 0.0f || Math::Length(mRotateVelocity) > 0.0f)
		{
			mYaw += mRotateVelocity.x;
			mPitch += mRotateVelocity.y;
			mRotateVelocity = Vector2::ZERO;

			mPitch = Math::Max(mPitch, -float(Math::EDX_PI_2));
			mPitch = Math::Min(mPitch, float(Math::EDX_PI_2));

			Matrix mCamRotate = Matrix::YawPitchRow(Math::ToDegrees(mYaw), Math::ToDegrees(mPitch), 0.0f);

			Vector3 vWorldUp, vWorldAhead;
			Vector3 vLocalUp = Vector3(0.0f, 1.0f, 0.0f), vLocalAhead = Vector3(0.0f, 0.0f, 1.0f);

			vWorldUp = Matrix::TransformVector(vLocalUp, mCamRotate);
			vWorldAhead = Matrix::TransformVector(vLocalAhead, mCamRotate);

			Vector3 vAcceleration = Vector3::ZERO;

			// Update velocities
			if (Math::Length(mMovementImpulse) > 0.0f)
			{
				float fMoveScaler = mMoveScaler;
				if (KeyPressed(VK_SHIFT))
					fMoveScaler *= 10.0f;
				else if (KeyPressed(VK_CONTROL))
					fMoveScaler *= 0.1f;

				vAcceleration = fDeltaTime * Math::Normalize(mMovementImpulse) * fMoveScaler;
				mMovementImpulse = Vector3::ZERO;

				mMovementVelocity += vAcceleration;
			}

			Vector3 vWorldPosDelta = Matrix::TransformVector(mMovementVelocity, mCamRotate);

			mPos += vWorldPosDelta;
			mTarget = mPos + vWorldAhead;
			mDir = Math::Normalize(mTarget - mPos);
			mUp = vWorldUp;

			mView = Matrix::LookAt(mPos, mTarget, mUp);
			mViewInv = Matrix::Inverse(mView);
			mRasterToWorld = Matrix::Mul(mViewInv, mRasterToCamera);
			mWorldToRaster = Matrix::Inverse(mRasterToWorld);
		}

		// Apply velocity damping
		{
			const float fMovementVelocityDampingAmount = 10.0f;
			const float fDampingFactor = Math::Clamp(fMovementVelocityDampingAmount * fDeltaTime, 0.0f, 0.75f);

			// Decelerate
			mMovementVelocity += -mMovementVelocity * fDampingFactor;
		}
	}

	void Camera::HandleMouseMsg(const MouseEventArgs& args)
	{
		switch (args.Action)
		{
		case MouseAction::Move:
			if (args.lDown)
			{
				Vector2 vMouseDelta;
				vMouseDelta.x = float(args.motionX);
				vMouseDelta.y = float(args.motionY);

				mRotateVelocity = mRotateScaler * vMouseDelta;

				Transform();
			}
			break;
		}
	}

	void Camera::HandleKeyboardMsg(const KeyboardEventArgs& args)
	{
		//switch (args.key)
		//{
		//case 'W':
		//	mDirKB.z += 1.0f;
		//	break;
		//case 'S':
		//	mDirKB.z -= 1.0f;
		//	break;
		//case 'A':
		//	mDirKB.x -= 1.0f;
		//	break;
		//case 'D':
		//	mDirKB.x += 1.0f;
		//	break;
		//case 'Q':
		//	mDirKB.y -= 1.0f;
		//	break;
		//case 'E':
		//	mDirKB.y += 1.0f;
		//	break;
		//}
	}
}