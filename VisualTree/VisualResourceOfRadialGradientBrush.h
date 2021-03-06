#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "GammaParameter.h"
#include "ExtendModeParameter.h"
#include "VisualResource.h"
#include "VisualResourceEntity.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>放射グラデーションブラシインスタンス。</summary>
	public ref class VisualResourceOfRadialGradientBrush sealed
        : public VisualResource
    {
    public:
        /// <summary>グラデーション境界の位置と色を格納する。</summary>
        ref class GradientStop
        {
        private:
            // 色
            Color color;

            // 位置
            float position;

        public:
            /// <summary>色設定を設定、取得する。</summary>
            property Color GradientColor {
                Color get() { return this->color; }
                void set(Color val) { this->color = val; }
            }

            /// <summary>位置設定を設定、取得する。</summary>
            property float Position {
                float get() { return this->position; }
                void set(float val) { this->position = val; }
            }

        public:
            /// <summary>コンストラクタ。</summary>
            /// <param name="edgeColor">色。</param>
            /// <param name="position">位置。</param>
            GradientStop(Color edgeColor, float position)
                : color(edgeColor), position(position)
            {}
        };

        /// <summary>グラデーションの原点のオフセット、グラデーション楕円のサイズと位置を格納。</summary>
        ref class RadialGradientBrushProperties
        {
        private:
            // グラデーション楕円の中心
            PointF  center;

            // グラデーション楕円の中心と相対的なグラデーション原点のオフセット
            PointF  gradientOriginOffset;

            // グラデーション楕円のX半径
            float   radiusX;

            // グラデーション楕円のY半径
            float   radiusY;

        public:
            /// <summary>グラデーション楕円の中心を設定、取得する。</summary>
            property PointF Center {
                PointF get() { return this->center; }
                void set(PointF pos) { this->center = pos; }
            }

            /// <summary>グラデーション楕円の中心と相対的なグラデーション原点のオフセットを設定、取得する。</summary>
            property PointF GradientOriginOffset {
                PointF get() { return this->gradientOriginOffset; }
                void set(PointF pos) { this->gradientOriginOffset = pos; }
            }

            /// <summary>グラデーション楕円のX半径を設定、取得する。</summary>
            property float RadiusX {
                float get() { return this->radiusX; }
                void set(float pos) { this->radiusX = pos; }
            }

            /// <summary>グラデーション楕円のY半径を設定、取得する。</summary>
            property float RadiusY {
                float get() { return this->radiusY; }
                void set(float pos) { this->radiusY = pos; }
            }
        };

	private:
        // グラデーション境界の位置と色リスト
        List<GradientStop^>^ gradientStops;

        // ガンマ色空間
        GammaParameter gamma;

        // 色の引き延ばし設定
        ExtendModeParameter extendMode;

        // グラデーションの原点のオフセット、グラデーション楕円のサイズと位置
        RadialGradientBrushProperties ^ properties;

    public:
        /// <summary>ガンマ色空間設定を設定、取得する。</summary>
        property GammaParameter Gamma {
            GammaParameter get() { return this->gamma; }
            void set(GammaParameter gamma) { this->gamma = gamma; }
        }

        /// <summary>色の引き延ばし設定を設定、取得する。</summary>
        property ExtendModeParameter ExtendMode {
            ExtendModeParameter get() { return this->extendMode; }
            void set(ExtendModeParameter mode) { this->extendMode = mode; }
        }

        /// <summary>グラデーションの原点のオフセット、グラデーション楕円のサイズと位置を設定、取得する。</summary>
        property RadialGradientBrushProperties ^ Propertes {
            RadialGradientBrushProperties ^ get() { return this->properties; }
        }

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
		VisualResourceOfRadialGradientBrush(String ^ name)
			: VisualResource(name),
              gamma(GammaParameter::GAMMA_2_2),
              extendMode(ExtendModeParameter::EXTEND_MODE_CLAMP)
        {
            this->gradientStops = gcnew List<GradientStop^>();
            this->properties = gcnew RadialGradientBrushProperties();
        }

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfRadialGradientBrush() {}

	public:
        /// <summary>グラデーション境界の位置と色を全て消去する。</summary>
        void ClearGradientStops()
        {
            this->gradientStops->Clear();
        }

        /// <summary>グラデーション境界の位置と色を追加する。</summary>
        void AddGradientStop(Color edgeColor, float position)
        {
            this->gradientStops->Add(gcnew GradientStop(edgeColor, position));
        }

        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            // グラデーション境界の位置と色をリスト化する
            std::vector<D2D1_GRADIENT_STOP> pos;
            if (this->gradientStops->Count > 0) {
                for each (GradientStop^ stp in this->gradientStops) {
                    D2D1_GRADIENT_STOP st;
                    st.color = D2D1::ColorF(stp->GradientColor.R / 255.0f,
                        stp->GradientColor.G / 255.0f,
                        stp->GradientColor.B / 255.0f,
                        stp->GradientColor.A / 255.0f);
                    st.position = stp->Position;
                    pos.push_back(st);
                }
            }
            else {
                D2D1_GRADIENT_STOP st;
                st.color = D2D1::ColorF(1, 1, 1, 1);
                st.position = 1;
                pos.push_back(st);
            }
            
            // グラデーション設定を行う
            ID2D1GradientStopCollection * gradientStops = NULL;
            ID2D1RadialGradientBrush * brush = NULL;
            HRESULT hr = renderTarget->CreateGradientStopCollection(pos.data(),
                                                                    (UINT32)pos.size(),
                                                                    (D2D1_GAMMA)this->gamma,
                                                                    (D2D1_EXTEND_MODE)this->extendMode,
                                                                    &gradientStops);
            if (SUCCEEDED(hr)) {
                D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES props = D2D1::RadialGradientBrushProperties(
                    D2D1::Point2F(this->properties->Center.X, this->properties->Center.Y),
                    D2D1::Point2F(this->properties->GradientOriginOffset.X, this->properties->GradientOriginOffset.Y),
                    this->properties->RadiusX,
                    this->properties->RadiusY);
                renderTarget->CreateRadialGradientBrush(props, gradientStops, &brush);
                gradientStops->Release();
            }
            return gcnew VisualResourceEntityOfBrush(this, brush);
        }
    };
}
