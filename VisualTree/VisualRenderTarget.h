#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Ellipse.h"
#include "AntialiasMode.h"
#include "BitmapInterpolationMode.h"
#include "OpacityMaskContent.h"
#include "VisualResources.h"
#include "VisualResourceEntity.h"
#include "VisualLayer.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>描画対象インスタンス。</summary>
    public value struct VisualRenderTarget
    {
    private:
        // レンダリングターゲット
        ID2D1DCRenderTarget * renderTarget;

    internal:
        /// <summary>コンストラクタ。</summary>
        /// <param name="renderTarget">レンダリングターゲット。</param>
        VisualRenderTarget(ID2D1DCRenderTarget * renderTarget)
            : renderTarget(renderTarget)
        {}

    public:
        //-----------------------------------------------------------------------------
        // 座標変換
        //-----------------------------------------------------------------------------
        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform();

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(int offsetX, int offsetY);

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        void SetTransform(Matrix matrix);

        /// <summary>後続のすべての描画操作がクリップされる四角形を指定します。</summary>
        /// <param name="rect">クリッピング領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="mode">アンチエイリアシングモード。</param>
        void PushAxisAlignedClip(RectangleF rect, AntialiasMode mode);

        /// <summary>レンダーターゲットから軸に平行な最後のクリップを削除します。</summary>
        void PopAxisAlignedClip();

        //-----------------------------------------------------------------------------
        // 合成設定
        //-----------------------------------------------------------------------------
        /// <summary>アンチエイリアスを設定する。</summary>
        /// <param name="mode">アンチエイリアスモード。</param>
        void SetAntialiasMode(AntialiasMode mode);

        //-----------------------------------------------------------------------------
        // 背景色クリア
        //-----------------------------------------------------------------------------
        /// <summary>描画領域を指定された色にクリアします。</summary>
        /// <param name="color">クリアする色。</param>
        void Clear(Color color);

        /// <summary>描画領域を指定された色にクリアします。</summary>
        /// <param name="red">赤色成分。</param>
        /// <param name="green">緑色成分。</param>
        /// <param name="blue">青色成分。</param>
        /// <param name="alpha">等価色成分。</param>
        void Clear(int red, int green, int blue, int alpha);

        //-----------------------------------------------------------------------------
        // レイヤー制御
        //-----------------------------------------------------------------------------
        /// <summary>レイヤーを作成する。</summary>
        /// <return>作成されたレイヤー。</return>
        VisualLayer ^ CreateLayer();

        /// <summary>レイヤーを作成する。</summary>
        /// <param name="name">レイヤーサイズ。</param>
        /// <return>作成されたレイヤー。</return>
        VisualLayer ^ CreateLayer(SizeF size);

        /// <summary>PopLayer が呼び出されるまでレンダーターゲットで後続の描画操作をすべて受け取ることができるように、指定されたレイヤーをそのレンダー ターゲットに追加します。</summary>
        /// <param name="layer">設定するレイヤー。</param>
        void PushLayer(VisualLayer ^ layer);

        /// <summary>PushLayerの最後の呼び出しで指定されたレイヤーに描画操作がリダイレクトされないようにします。</summary>
        void PopLayer();

        //-----------------------------------------------------------------------------
        // 描画API
        //-----------------------------------------------------------------------------
        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity, BitmapInterpolationMode interpolationMode);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, BitmapInterpolationMode interpolationMode);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity, BitmapInterpolationMode interpolationMode);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="destinationRectangle">レンダー ターゲットの座標空間における、ビットマップが描画される領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="opacity">ビットマップに適用する不透明度の値を指定する 0.0f 〜 1.0f の値。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="interpolationMode">描画操作によってビットマップのサイズ調整または回転が行われるときに使用する補間モード。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, BitmapInterpolationMode interpolationMode);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        /// <param name="sourceRectangle">ビットマップの座標空間における、ビットマップ内の描画する領域のサイズと位置 (デバイス非依存のピクセル単位)。</param>
        void DrawBitmapSource(VisualResourceEntity ^ bitmap, RectangleF sourceRectangle);

        /// <summary>指定されたビットマップを、指定された四角形のサイズに拡大または縮小した後に描画します。</summary>
        /// <param name="bitmap">レンダリングするビットマップ。</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap);

        /// <summary>指定された寸法とストロークで楕円の輪郭を描画します。</summary>
        /// <param name="rect">描画する楕円の位置と半径。</param>
        /// <param name="brush">楕円の輪郭の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">楕円のストロークの太さ。</param>
        void DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>指定された寸法とストロークで楕円の輪郭を描画します。</summary>
        /// <param name="rect">描画する楕円の位置と半径。</param>
        /// <param name="brush">楕円の輪郭の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">楕円のストロークの太さ。</param>
        /// <param name="strokeStyle">ストロークスタイル。</param>
        void DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>指定された寸法とストロークで楕円の輪郭を描画します。</summary>
        /// <param name="ellipse">楕円領域。</param>
        /// <param name="brush">楕円の輪郭の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">楕円のストロークの太さ。</param>
        void DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>指定された寸法とストロークで楕円の輪郭を描画します。</summary>
        /// <param name="ellipse">楕円領域。</param>
        /// <param name="brush">楕円の輪郭の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">楕円のストロークの太さ。</param>
        /// <param name="strokeStyle">ストロークスタイル。</param>
        void DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>指定されたジオメトリの輪郭を描画します。</summary>
        /// <param name="geometry">描画ジオメトリ。</param>
        /// <param name="brush">ストロークを塗りつぶすブラシ。</param>
        /// <param name="strokeWidth">ストロークの太さ。</param>
        void DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>指定されたジオメトリの輪郭を描画します。</summary>
        /// <param name="geometry">描画ジオメトリ。</param>
        /// <param name="brush">ストロークを塗りつぶすブラシ。</param>
        /// <param name="strokeWidth">ストロークの太さ。</param>
        /// <param name="strokeStyle">ストロークスタイル。</param>
        void DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        //this->renderTarget->DrawGlyphRun;

        /// <summary>指定されたストローク スタイルを使用して、指定された点の間に線を描画します。</summary>
        /// <param name="startPt">線の始点。</param>
        /// <param name="endPt">線の終点。</param>
        /// <param name="brush">線の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">線のストロークの太さ。</param>
        void DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>指定されたストローク スタイルを使用して、指定された点の間に線を描画します。</summary>
        /// <param name="startPt">線の始点。</param>
        /// <param name="endPt">線の終点。</param>
        /// <param name="brush">線の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">線のストロークの太さ。</param>
        void DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>矩形を描画します。</summary>
        /// <param name="rectangle">対象の矩形。</param>
        /// <param name="brush">線のブラシ。</param>
        /// <param name="strokeWidth">線のストロークの太さ。</param>
        void DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>矩形を描画します。</summary>
        /// <param name="rectangle">対象の矩形。</param>
        /// <param name="brush">線のブラシ。</param>
        /// <param name="strokeWidth">線のストロークの太さ。</param>
        /// <param name="strokeStyle">ストロークスタイル。</param>
        void DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>書式情報を使用して、指定された文字列を描画します。</summary>
        /// <param name="text">描画文字列。</param>
        /// <param name="format">書式情報。</param>
        /// <param name="rect">文字列が描画される領域のサイズと位置。</param>
        /// <param name="brush">描画に使用するブラシ。</param>
        void DrawText(String ^ text, VisualResourceEntity ^ format, RectangleF rect, VisualResourceEntity ^ brush);

        //this->renderTarget->DrawTextLayout;
        //this->renderTarget->FillRoundedRectangle;

        /// <summary>指定された楕円領域の内部を描画します。</summary>
        /// <param name="ellipse">楕円領域。</param>
        /// <param name="brush">楕円内部を塗りつぶすブラシ。</param>
        void FillEllipse(Ellipse ellipse, VisualResourceEntity ^ brush);

        /// <summary>指定されたジオメトリの内部を描画します。</summary>
        /// <param name="geometry">描画ジオメトリ。</param>
        /// <param name="brush">ジオメトリ内部を塗りつぶすブラシ。</param>
        void FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush);

        /// <summary>指定されたジオメトリの内部を描画します。</summary>
        /// <param name="geometry">描画ジオメトリ。</param>
        /// <param name="brush">ジオメトリ内部を塗りつぶすブラシ。</param>
        /// <param name="opacitybrush">ジオメトリに適用する不透明度マスク。</param>
        void FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, VisualResourceEntity ^ opacitybrush);

        //this->renderTarget->FillMesh;

        /// <summary>指定されたビットマップによって記述された不透明マスクをブラシに適用し、そのブラシを使用してレンダーターゲットの領域をペイントします。 </summary>
        /// <param name="bitmap">ブラシに適用する不透明マスク。</param>
        /// <param name="brush">レンダーターゲットの領域をペイントするために使用されるブラシ。</param>
        /// <param name="opacitybrush">不透明度マスクに含まれるコンテンツのタイプ。</param>
        void FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask);

        /// <summary>指定されたビットマップによって記述された不透明マスクをブラシに適用し、そのブラシを使用してレンダーターゲットの領域をペイントします。 </summary>
        /// <param name="bitmap">ブラシに適用する不透明マスク。</param>
        /// <param name="brush">レンダーターゲットの領域をペイントするために使用されるブラシ。</param>
        /// <param name="opacitybrush">不透明度マスクに含まれるコンテンツのタイプ。</param>
        /// <param name="destinationRectangle">描画するレンダーターゲットの領域。</param>
        void FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask, RectangleF destinationRectangle);

        /// <summary>指定されたビットマップによって記述された不透明マスクをブラシに適用し、そのブラシを使用してレンダーターゲットの領域をペイントします。 </summary>
        /// <param name="bitmap">ブラシに適用する不透明マスク。</param>
        /// <param name="brush">レンダーターゲットの領域をペイントするために使用されるブラシ。</param>
        /// <param name="opacitybrush">不透明度マスクに含まれるコンテンツのタイプ。</param>
        /// <param name="destinationRectangle">描画するレンダーターゲットの領域。</param>
        /// <param name="sourceRectangle">不透明マスクとして使用するビットマップの領域。</param>
        void FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask, RectangleF destinationRectangle, RectangleF sourceRectangle);

        /// <summary>塗りつぶされた矩形を描画します。</summary>
        /// <param name="rectangle">対象の矩形。</param>
        /// <param name="brush">内部を塗りつぶすブラシ。</param>
        void FillRectangle(RectangleF rectangle, VisualResourceEntity ^ brush);

        //this->renderTarget->FillRoundedRectangle;
    };
}

