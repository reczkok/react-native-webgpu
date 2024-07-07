#pragma once

#include <memory>

#include "webgpu/webgpu_cpp.h"

#include <RNFHybridObject.h>

#include "RNFJSIConverter.h"

namespace jsi = facebook::jsi;

namespace rnwgpu {
class GPUMultisampleState {
public:
  wgpu::MultisampleState *getInstance() { return &_instance; }

  wgpu::MultisampleState _instance;
};
} // namespace rnwgpu

namespace margelo {

template <> struct JSIConverter<std::shared_ptr<rnwgpu::GPUMultisampleState>> {
  static std::shared_ptr<rnwgpu::GPUMultisampleState>
  fromJSI(jsi::Runtime &runtime, const jsi::Value &arg, bool outOfBounds) {
    auto result = std::make_unique<rnwgpu::GPUMultisampleState>();
    if (!outOfBounds && arg.isObject()) {
      auto value = arg.getObject(runtime);
      if (value.hasProperty(runtime, "count")) {
        auto count = value.getProperty(runtime, "count");

        if (value.hasProperty(runtime, "count")) {
          result->_instance.count = count.getNumber();
        }
      }
      if (value.hasProperty(runtime, "mask")) {
        auto mask = value.getProperty(runtime, "mask");

        if (value.hasProperty(runtime, "mask")) {
          result->_instance.mask = mask.getNumber();
        }
      }
      if (value.hasProperty(runtime, "alphaToCoverageEnabled")) {
        auto alphaToCoverageEnabled =
            value.getProperty(runtime, "alphaToCoverageEnabled");
        if (value.hasProperty(runtime, "alphaToCoverageEnabled")) {
          result->_instance.alphaToCoverageEnabled =
              alphaToCoverageEnabled.getBool();
        }
      }
    }
    return result;
  }
  static jsi::Value toJSI(jsi::Runtime &runtime,
                          std::shared_ptr<rnwgpu::GPUMultisampleState> arg) {
    // No conversions here
    return jsi::Value::null();
  }
};
} // namespace margelo
