#include <iostream>
#include <memory>

// Базовий клас обробника
class Handler {
public:
    virtual void handleRequest(const std::string& request) const = 0;
    virtual std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> nextHandler) {
        nextHandler_ = nextHandler;
        return nextHandler;
    }

    virtual ~Handler() = default;

protected:
    std::shared_ptr<Handler> nextHandler_;
};

// Конкретний обробник A
class ConcreteHandlerA : public Handler {
public:
    void handleRequest(const std::string& request) const override {
        if (request == "A") {
            std::cout << "ConcreteHandlerA: Handling request 'A'\n";
        }
        else if (nextHandler_) {
            nextHandler_->handleRequest(request);
        }
    }
};

// Конкретний обробник B
class ConcreteHandlerB : public Handler {
public:
    void handleRequest(const std::string& request) const override {
        if (request == "B") {
            std::cout << "ConcreteHandlerB: Handling request 'B'\n";
        }
        else if (nextHandler_) {
            nextHandler_->handleRequest(request);
        }
    }
};

// Конкретний обробник C
class ConcreteHandlerC : public Handler {
public:
    void handleRequest(const std::string& request) const override {
        if (request == "C") {
            std::cout << "ConcreteHandlerC: Handling request 'C'\n";
        }
        else if (nextHandler_) {
            nextHandler_->handleRequest(request);
        }
    }
};

int main() {
    // Використання паттерна "Ланцюжок обов'язків"
    std::shared_ptr<Handler> handlerA = std::make_shared<ConcreteHandlerA>();
    std::shared_ptr<Handler> handlerB = std::make_shared<ConcreteHandlerB>();
    std::shared_ptr<Handler> handlerC = std::make_shared<ConcreteHandlerC>();

    handlerA->setNext(handlerB)->setNext(handlerC);

    // Послідовна передача запитів в ланцюжку
    handlerA->handleRequest("A");
    handlerA->handleRequest("B");
    handlerA->handleRequest("C");
    handlerA->handleRequest("D");

    return 0;
}
