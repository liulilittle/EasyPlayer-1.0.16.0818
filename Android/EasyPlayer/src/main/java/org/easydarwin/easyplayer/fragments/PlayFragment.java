package org.easydarwin.easyplayer.fragments;


import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.RectF;
import android.graphics.SurfaceTexture;
import android.graphics.drawable.ColorDrawable;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.ResultReceiver;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.view.ViewCompat;
import android.support.v4.view.ViewPropertyAnimatorListenerAdapter;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.widget.ImageView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.bumptech.glide.signature.StringSignature;

import org.easydarwin.easyplayer.PlayActivity;
import org.easydarwin.easyplayer.PlaylistActivity;
import org.easydarwin.easyplayer.TheApp;
import org.easydarwin.easyplayer.views.AngleView;
import org.easydarwin.video.EasyRTSPClient;
import org.easydarwin.video.RTSPClient;
import org.esaydarwin.rtsp.player.R;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.ref.WeakReference;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.UUID;

import uk.copywitchshame.senab.photoview.gestures.PhotoViewAttacher;

public class PlayFragment extends Fragment implements TextureView.SurfaceTextureListener, PhotoViewAttacher.OnMatrixChangedListener {
    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    public static final String ARG_PARAM1 = "param1";
    public static final String ARG_PARAM2 = "param2";
    public static final String ARG_PARAM3 = "param3";
    public static final int RESULT_REND_STARTED = 1;
    public static final int RESULT_REND_VIDEO_DISPLAYED = 2;
    public static final int RESULT_REND_STOPED = -1;

    protected static final String TAG = "PlayFragment";

    // TODO: Rename and change types of parameters
    protected String mUrl;
    protected int mType;

    protected EasyRTSPClient mStreamRender;
    protected ResultReceiver mResultReceiver;
    protected int mWidth;
    protected int mHeight;
    protected View.OnLayoutChangeListener listener;
    private PhotoViewAttacher mAttacher;
    private TextureView mSurfaceView;
    private AngleView mAngleView;
    private MediaScannerConnection mScanner;
    private ImageView mRenderCover;
    private AsyncTask<Void, Void, Bitmap> mLoadingPictureThumbTask;
    private ImageView mTakePictureThumb;
    private ResultReceiver mRR;
    protected ImageView cover;
    /**
     * 抓拍后隐藏thumb的task
     */
    private final Runnable mAnimationHiddenTakepictureThumbTask = new Runnable() {
        @Override
        public void run() {
            ViewCompat.animate(mTakePictureThumb).scaleX(0.0f).scaleY(0.0f).setListener(new ViewPropertyAnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(View view) {
                    super.onAnimationEnd(view);
                    view.setVisibility(View.INVISIBLE);
                }
            });
        }
    };

    public void setSelected(boolean selected) {
        mSurfaceView.animate().scaleX(selected ? 0.9f : 1.0f);
        mSurfaceView.animate().scaleY(selected ? 0.9f : 1.0f);
        mSurfaceView.animate().alpha(selected ? 0.7f : 1.0f);
    }

    public long getReceivedStreamLength() {
        if (mStreamRender != null) {
            return mStreamRender.receivedDataLength();
        }
        return 0;
    }

    public boolean onRecordOrStop() {
        if (!mStreamRender.isRecording()) {
            File f = new File(TheApp.sMoviePath);
            f.mkdirs();
            mStreamRender.startRecord(new File(f, new SimpleDateFormat("yy-MM-dd HH:mm:ss").format(new Date()) + ".mp4").getPath());
            return true;
        } else {
            mStreamRender.stopRecord();
            return false;
        }
    }

    public static class ReverseInterpolator extends AccelerateDecelerateInterpolator {
        @Override
        public float getInterpolation(float paramFloat) {
            return super.getInterpolation(1.0f - paramFloat);
        }
    }

    public static PlayFragment newInstance(String url, int type, ResultReceiver rr) {
        PlayFragment fragment = new PlayFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, url);
        args.putInt(ARG_PARAM2, type);
        args.putParcelable(ARG_PARAM3, rr);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mUrl = getArguments().getString(ARG_PARAM1);
            mType = getArguments().getInt(ARG_PARAM2);
            mRR = getArguments().getParcelable(ARG_PARAM3);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, final ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View view = inflater.inflate(R.layout.fragment_play, container, false);
        view.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PlayActivity activity = (PlayActivity) getActivity();
                activity.onPlayFragmentClicked(PlayFragment.this);
            }
        });

        cover = (ImageView) view.findViewById(R.id.surface_cover);
//        Glide.with(this).load(PlaylistActivity.url2localPosterFile(getActivity(), mUrl)).diskCacheStrategy(DiskCacheStrategy.NONE).placeholder(R.drawable.placeholder).into(new ImageViewTarget<GlideDrawable>(cover) {
//            @Override
//            protected void setResource(GlideDrawable resource) {
//                int width = resource.getIntrinsicWidth();
//                int height = resource.getIntrinsicHeight();
//                fixPlayerRatio(view, container.getWidth(), container.getHeight(), width, height);
//                cover.setImageDrawable(resource);
//            }
//        });

        if (!TextUtils.isEmpty(mUrl)) {
            Glide.with(this).load(PlaylistActivity.url2localPosterFile(getActivity(), mUrl)).signature(new StringSignature(UUID.randomUUID().toString())).fitCenter().into(cover);
        }
        return view;
    }

    @Override
    public void onViewCreated(final View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        mSurfaceView = (TextureView) view.findViewById(R.id.surface_view);
        mSurfaceView.setOpaque(false);
        mSurfaceView.setSurfaceTextureListener(this);
        mAngleView = (AngleView) getView().findViewById(R.id.render_angle_view);
        mRenderCover = (ImageView) getView().findViewById(R.id.surface_cover);
        mTakePictureThumb = (ImageView) getView().findViewById(R.id.live_video_snap_thumb);
        mResultReceiver = new ResultReceiver(new Handler()) {
            @Override
            protected void onReceiveResult(int resultCode, Bundle resultData) {
                super.onReceiveResult(resultCode, resultData);
                if (resultCode == EasyRTSPClient.RESULT_VIDEO_DISPLAYED) {
//                    Toast.makeText(PlayActivity.this, "视频正在播放了", Toast.LENGTH_SHORT).show();
                    view.findViewById(android.R.id.progress).setVisibility(View.GONE);
                    mSurfaceView.post(new Runnable() {
                        @Override
                        public void run() {
                            if (mWidth != 0 && mHeight != 0) {
                                Bitmap e = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
                                mSurfaceView.getBitmap(e);
                                File f = PlaylistActivity.url2localPosterFile(mSurfaceView.getContext(), mUrl);
                                saveBitmapInFile(f.getPath(), e);
                                e.recycle();
                            }
                        }
                    });
                    cover.setVisibility(View.GONE);
                    mRR.send(RESULT_REND_VIDEO_DISPLAYED, null);
                } else if (resultCode == EasyRTSPClient.RESULT_VIDEO_SIZE) {
                    mWidth = resultData.getInt(EasyRTSPClient.EXTRA_VIDEO_WIDTH);
                    mHeight = resultData.getInt(EasyRTSPClient.EXTRA_VIDEO_HEIGHT);
                    if (mAttacher != null) {
                        mAttacher.cleanup();
                    }
                    if (!isLandscape()) {

                        ViewGroup parent = (ViewGroup) view.getParent();
                        parent.addOnLayoutChangeListener(listener);
                        fixPlayerRatio(view, parent.getWidth(), parent.getHeight());


                        mAttacher = new PhotoViewAttacher(mSurfaceView, mWidth, mHeight);
                        mAttacher.setScaleType(ImageView.ScaleType.CENTER_CROP);
                        mAttacher.setOnMatrixChangeListener(PlayFragment.this);
                        mAttacher.update();
                        mAngleView.setVisibility(View.VISIBLE);
                    }
                } else if (resultCode == EasyRTSPClient.RESULT_TIMEOUT) {
                    Toast.makeText(getActivity(), "试播时间到", Toast.LENGTH_SHORT).show();
                }
            }
        };

        listener = new View.OnLayoutChangeListener() {
            @Override
            public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom) {
                Log.d(TAG, String.format("onLayoutChange left:%d,top:%d,right:%d,bottom:%d->oldLeft:%d,oldTop:%d,oldRight:%d,oldBottom:%d", left, top, right, bottom, oldLeft, oldTop, oldRight, oldBottom));
                if (right - left != oldRight - oldLeft || bottom - top != oldBottom - oldTop) {
                    if (!isLandscape()) {
                        fixPlayerRatio(view, right - left, bottom - top);
                    } else {
                        PlayActivity activity = (PlayActivity) getActivity();
                        if (!activity.multiWindows()) {
                            view.getLayoutParams().width = ViewGroup.LayoutParams.MATCH_PARENT;
                            view.getLayoutParams().height = ViewGroup.LayoutParams.MATCH_PARENT;
                            view.requestLayout();
                        } else {
                            fixPlayerRatio(view, right - left, bottom - top);
                        }
                    }
                }
            }
        };
        ViewGroup parent = (ViewGroup) view.getParent();
        parent.addOnLayoutChangeListener(listener);
    }

    @Override
    public void onDestroyView() {
        ViewGroup parent = (ViewGroup) getView().getParent();
        parent.removeOnLayoutChangeListener(listener);
        super.onDestroyView();
    }

    protected boolean isLandscape() {
        return getActivity().getRequestedOrientation() == ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE || getActivity().getRequestedOrientation() == ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE;
    }

    protected void fixPlayerRatio(View renderView, int widthSize, int heightSize, int width, int height) {
        if (width == 0 || height == 0) {
            return;
        }
        float aspectRatio = width * 1.0f / height;
        if (widthSize > heightSize * aspectRatio) {
            height = heightSize;
            width = (int) (height * aspectRatio);
        } else {
            width = widthSize;
            height = (int) (width / aspectRatio);
        }
        renderView.getLayoutParams().width = width;
        renderView.getLayoutParams().height = height;
        renderView.requestLayout();
    }

    /**
     * 高度固定，宽度可更改；
     *
     * @param renderView
     * @param maxWidth
     * @param maxHeight
     */
    protected void fixPlayerRatio(View renderView, int maxWidth, int maxHeight) {
//        fixPlayerRatio(renderView, maxWidth, maxHeight, mWidth, mHeight);
    }

    protected void startRending(Surface surface) {
        mStreamRender = new EasyRTSPClient(getContext(), "E2E90B0867DBB86BF1450BCD01664592", surface, mResultReceiver);
        mStreamRender.start(mUrl, mType, RTSPClient.EASY_SDK_VIDEO_FRAME_FLAG | RTSPClient.EASY_SDK_AUDIO_FRAME_FLAG, "admin", "admin");
        mRR.send(RESULT_REND_STARTED, null);
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        startRending(new Surface(surface));
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        if (mAttacher != null) {
            mAttacher.update();
        }
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        if (mStreamRender != null) {
            mRR.send(RESULT_REND_STOPED, null);
            mStreamRender.stop();
            mStreamRender = null;
        }
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }

    @Override
    public void onMatrixChanged(RectF rect) {
        float maxMovement = (rect.width() - mSurfaceView.getWidth());
        float middle = mSurfaceView.getWidth() * 0.5f + mSurfaceView.getLeft();
        float currentMiddle = rect.width() * 0.5f + rect.left;
        mAngleView.setCurrentProgress(-(int) ((currentMiddle - middle) * 100 / maxMovement));
    }

    public void takePicture(final String path) {
        try {
            Bitmap bitmap = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
            mSurfaceView.getBitmap(bitmap);
            saveBitmapInFile(path, bitmap);
            bitmap.recycle();

            mRenderCover.setImageDrawable(new ColorDrawable(getResources().getColor(android.R.color.white)));
            mRenderCover.setVisibility(View.VISIBLE);
            mRenderCover.setAlpha(1.0f);
            ViewCompat.animate(mRenderCover).cancel();
            ViewCompat.animate(mRenderCover).alpha(0.3f).setListener(new ViewPropertyAnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(View view) {
                    super.onAnimationEnd(view);
                    mRenderCover.setVisibility(View.GONE);
                }
            });
            if (mLoadingPictureThumbTask != null) mLoadingPictureThumbTask.cancel(true);
            final int w = mTakePictureThumb.getWidth();
            final int h = mTakePictureThumb.getHeight();
            mLoadingPictureThumbTask = new AsyncTask<Void, Void, Bitmap>() {
                final WeakReference<ImageView> mImageViewRef = new WeakReference<>(mTakePictureThumb);
                final String mPath = path;

                @Override
                protected Bitmap doInBackground(Void... params) {
                    return decodeSampledBitmapFromResource(mPath, w, h);
                }

                @Override
                protected void onPostExecute(Bitmap bitmap) {
                    super.onPostExecute(bitmap);
                    if (isCancelled()) {
                        bitmap.recycle();
                        return;
                    }
                    ImageView iv = mImageViewRef.get();
                    if (iv == null) return;
                    iv.setImageBitmap(bitmap);
                    iv.setVisibility(View.VISIBLE);
                    iv.removeCallbacks(mAnimationHiddenTakepictureThumbTask);
                    iv.clearAnimation();
                    ViewCompat.animate(iv).scaleX(1.0f).scaleY(1.0f).setListener(new ViewPropertyAnimatorListenerAdapter() {
                        @Override
                        public void onAnimationEnd(View view) {
                            super.onAnimationEnd(view);
                            view.postOnAnimationDelayed(mAnimationHiddenTakepictureThumbTask, 4000);
                        }
                    });
                    iv.setTag(mPath);
                }
            }.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);

        } catch (OutOfMemoryError error) {
            error.printStackTrace();
        } catch (IllegalStateException e) {
            e.printStackTrace();
        }
    }

    public static Bitmap decodeSampledBitmapFromResource(String path,
                                                         int reqWidth, int reqHeight) {

        // First decode with inJustDecodeBounds=true to check dimensions
        final BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeFile(path, options);

        // Calculate inSampleSize
        options.inSampleSize = calculateInSampleSize(options, reqWidth, reqHeight);

        // Decode bitmap with inSampleSize set
        options.inJustDecodeBounds = false;
        return BitmapFactory.decodeFile(path, options);
    }

    public static int calculateInSampleSize(
            BitmapFactory.Options options, int reqWidth, int reqHeight) {
        // Raw height and width of image
        final int height = options.outHeight;
        final int width = options.outWidth;
        int inSampleSize = 1;

        if (height > reqHeight || width > reqWidth) {

            final int halfHeight = height / 2;
            final int halfWidth = width / 2;

            // Calculate the largest inSampleSize value that is a power of 2 and keeps both
            // height and width larger than the requested height and width.
            while ((halfHeight / inSampleSize) > reqHeight
                    && (halfWidth / inSampleSize) > reqWidth) {
                inSampleSize *= 2;
            }
        }

        return inSampleSize;
    }

    private void saveBitmapInFile(final String path, Bitmap bitmap) {
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(path);
            bitmap.compress(Bitmap.CompressFormat.JPEG, 90, fos);
            if (mScanner == null) {
                MediaScannerConnection connection = new MediaScannerConnection(getContext(),
                        new MediaScannerConnection.MediaScannerConnectionClient() {
                            public void onMediaScannerConnected() {
                                mScanner.scanFile(path, null /* mimeType */);
                            }

                            public void onScanCompleted(String path1, Uri uri) {
                                if (path1.equals(path)) {
                                    mScanner.disconnect();
                                    mScanner = null;
                                }
                            }
                        });
                try {
                    connection.connect();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                mScanner = connection;
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (OutOfMemoryError error) {
            error.printStackTrace();
        } finally {
            if (fos != null) {
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public boolean toggleAudioEnable() {
        if (mStreamRender == null) {
            return false;
        }
        mStreamRender.setAudioEnable(!mStreamRender.isAudioEnable());
        return mStreamRender.isAudioEnable();
    }

    public void setUrl(String url) {
        this.mUrl = url;
        if (!TextUtils.isEmpty(mUrl)) {
            Glide.with(this).load(PlaylistActivity.url2localPosterFile(getActivity(), mUrl)).signature(new StringSignature(UUID.randomUUID().toString())).fitCenter().into(cover);
        }
    }

    public void setTransType(int transType) {
        this.mType = transType;
    }

    public void setResultReceiver(ResultReceiver rr) {
        mRR = rr;
    }

    public boolean isAudioEnable() {
        return mStreamRender != null && mStreamRender.isAudioEnable();
    }
}
