﻿// (c) gosha20777 (github.com/gosha20777), 2019, MIT License

#pragma once
#include "../baseLayer.h"

namespace keras2cpp{
    namespace layers{
        class ELU final : public Layer<ELU> {
            float alpha_{1.f};

        public:
            ELU(Stream& file);
            Tensor operator()(const Tensor& in) const noexcept override;
        };
    }
}