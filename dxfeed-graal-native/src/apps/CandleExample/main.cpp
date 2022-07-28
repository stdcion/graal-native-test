#include <api/Api.h>
#include <iostream>
#include <string>
#include "dxfeed_c_api.h"
#include "api/DxFeed.hpp"

std::string candleToString(dxfeed_candle candle) {
  return std::string("Candle{") + candle.eventSymbol +
      std::string(", eventTime=") + std::to_string(candle.eventTime) +
      std::string(", eventFlags=") + std::to_string(candle.eventFlags) +
      std::string(", time=") + std::to_string(candle.time) +
      std::string(", count=") + std::to_string(candle.count) +
      std::string(", open=") + std::to_string(candle.open) +
      std::string(", high=") + std::to_string(candle.high) +
      std::string(", low=") + std::to_string(candle.low) +
      std::string(", close=") + std::to_string(candle.close) +
      std::string(", volume=") + std::to_string(candle.volume) +
      std::string(", vwap=") + std::to_string(candle.VWAP) +
      std::string(", bidVolume=") + std::to_string(candle.bidVolume) +
      std::string(", askVolume=") + std::to_string(candle.askVolume) +
      std::string(", impVolatility=") + std::to_string(candle.impVolatility) +
      std::string(", openInterest=") + std::to_string(candle.openInterest) +
      "}";
}

int main() {
  auto feed = dxfeed_get_instance();
  auto connection = dxfeed_create_connection(feed, "demo.dxfeed.com:7300");
  auto listener = [](const void *events, int count) {
    auto candleList = (dxfeed_candle *) events;
    std::cout << "Candles count: " << count << std::endl;
    for (int i = 0; i < count; ++i) {
      dxfeed_candle candle = candleList[i];
      std::cout << candleToString(candle) << std::endl;
    };
  };

  dxfeed_get_candle_snapshot(connection,
                             listener,
                             "AAPL{=d}",
                             0,
                             1658502278000,
                             20000);
}