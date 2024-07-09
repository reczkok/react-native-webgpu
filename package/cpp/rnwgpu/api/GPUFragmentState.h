#pragma once

#include <memory>
#include <string>

#include "webgpu/webgpu_cpp.h"

#include "Logger.h"
#include "RNFJSIConverter.h"
#include <RNFHybridObject.h>

namespace jsi = facebook::jsi;

namespace rnwgpu {

class GPUFragmentState {
public:
  wgpu::FragmentState *getInstance() { return &_instance; }

  wgpu::FragmentState _instance;

  std::string entryPoint;
};
} // namespace rnwgpu

namespace margelo {

template <> struct JSIConverter<std::shared_ptr<rnwgpu::GPUFragmentState>> {
  static std::shared_ptr<rnwgpu::GPUFragmentState>
  fromJSI(jsi::Runtime &runtime, const jsi::Value &arg, bool outOfBounds) {
    auto result = std::make_unique<rnwgpu::GPUFragmentState>();
    if (!outOfBounds && arg.isObject()) {
      auto value = arg.getObject(runtime);
      if (value.hasProperty(runtime, "targets")) {
        auto targets = value.getProperty(runtime, "targets");

        if (targets.isUndefined()) {
          throw std::runtime_error(
              "Property GPUFragmentState::targets is required");
        }
      } else {
        throw std::runtime_error(
            "Property GPUFragmentState::targets is not defined");
      }
      if (value.hasProperty(runtime, "module")) {
        auto module = value.getProperty(runtime, "module");

        if (module.isUndefined()) {
          throw std::runtime_error(
              "Property GPUFragmentState::module is required");
        }
      } else {
        throw std::runtime_error(
            "Property GPUFragmentState::module is not defined");
      }
      if (value.hasProperty(runtime, "entryPoint")) {
        auto entryPoint = value.getProperty(runtime, "entryPoint");

        if (entryPoint.isString()) {
          auto str = entryPoint.asString(runtime).utf8(runtime);
          result->entryPoint = str;
          result->_instance.entryPoint = result->entryPoint.c_str();
        }
      }
      if (value.hasProperty(runtime, "constants")) {
        auto constants = value.getProperty(runtime, "constants");
      }
    }
    rnwgpu::Logger::logToConsole("GPUFragmentState::targets = %f",
                                 result->_instance.targets);
    rnwgpu::Logger::logToConsole("GPUFragmentState::module = %f",
                                 result->_instance.module);
    rnwgpu::Logger::logToConsole("GPUFragmentState::entryPoint = %f",
                                 result->_instance.entryPoint);
    rnwgpu::Logger::logToConsole("GPUFragmentState::constants = %f",
                                 result->_instance.constants);
    return result;
  }
  static jsi::Value toJSI(jsi::Runtime &runtime,
                          std::shared_ptr<rnwgpu::GPUFragmentState> arg) {
    // No conversions here
    return jsi::Value::null();
  }
};
} // namespace margelo
