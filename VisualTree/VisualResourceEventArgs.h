#pragma once
#include "VisualResources.h"

using namespace System;
using namespace System::Collections::Generic;

namespace VisualTree
{
    /// <summary>リソース作成イベントオブジェクト。</summary>
    public ref class VisualResourceEventArgs
        : EventArgs
    {
    private:
        // リソースコレクション
        List<VisualResource ^>^ srcres;

    public:
        /// <summary>リソースコレクションを取得する。</summary>
        property List<VisualResource ^>^ Resources {
            List<VisualResource ^>^ get() { return this->srcres; }
        }

    public:
    	/// <summary>コンストラクタ。</summary>
        /// <param name="srcres">リソースコレクション。</param>
        VisualResourceEventArgs(List<VisualResource ^>^ srcres)
            : srcres(srcres)
        {}
    };
}