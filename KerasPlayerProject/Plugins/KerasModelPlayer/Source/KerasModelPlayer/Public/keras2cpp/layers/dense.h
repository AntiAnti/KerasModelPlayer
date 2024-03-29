﻿// (c) gosha20777 (github.com/gosha20777), 2019, MIT License

#pragma once
#include "activation.h"
namespace keras2cpp{
    namespace layers{
        class Dense final : public Layer<Dense> {
            Tensor weights_;
            Tensor biases_;
            Activation activation_;
        public:
            Dense(Stream& file);
            Tensor operator()(const Tensor& in) const noexcept override;
        };
    }
}
