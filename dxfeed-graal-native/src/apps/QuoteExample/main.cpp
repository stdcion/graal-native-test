#include <api/Api.h>
#include <iostream>
#include <string>
#include "api/DxFeed.hpp"

std::string quoteToString(dxfeed_quote quote)  {
  return std::string("Quote{") + quote.eventSymbol +
      std::string(", eventTime=") + std::to_string(quote.eventTime) +
      std::string(", time=") + std::to_string(quote.time) +
      std::string(", timeNanos=") + std::to_string(quote.timeNanos) +
      std::string(", timeNanoPart=") + std::to_string(quote.timeNanoPart) +
      std::string(", sequence=") + std::to_string(quote.sequnce) +
      std::string(", bidTime=") + std::to_string(quote.bidTime) +
      std::string(", bidExchange=") + quote.bidExchangeCode +
      std::string(", bidPrice=") + std::to_string(quote.bidPrice) +
      std::string(", bidSize=") + std::to_string(quote.bidSize) +
      std::string(", askTime=") + std::to_string(quote.askTime) +
      std::string(", askExchange=") + quote.askExchangeCode +
      std::string(", askPrice=") + std::to_string(quote.askPrice) +
      std::string(", askSize=") + std::to_string(quote.askSize) +
      "}";
}

int main() {
  auto feed = dxfeed_get_instance();
  //((dxfeed::DxFeed*)feed)->setSystemProperty("dxfeed.aggregationPeriod", "15s");
  ((dxfeed::DxFeed*)feed)->setSystemProperty("dxscheme.fob", "false");
  //auto connection = dxfeed_create_connection(feed, "demo.dxfeed.com:7300");
  auto connection = dxfeed_create_connection(feed, "mddqa.in.devexperts.com:7400");
  auto subscription = dxfeed_create_subscription(connection, 0);
  dxfeed_add_listener(subscription, [](const void *events, int count) {
    auto quoteList = (dxfeed_quote *) events;
    std::cout << "Quotes count: " << count << std::endl;
    for (int i = 0; i < count; ++i) {
      dxfeed_quote quote = quoteList[i];
      std::cout << quoteToString(quote) << std::endl;
    }
  });
  dxfeed_add_symbol(subscription, "AAPL");
  std::cin.get();
}