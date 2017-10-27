#pragma once

#include <mbgl/style/expression/expression.hpp>
#include <mbgl/style/expression/parsing_context.hpp>
#include <mbgl/style/conversion.hpp>

#include <memory>
#include <map>

namespace mbgl {
namespace style {
namespace expression {

class Let : public Expression {
public:
    using Bindings = std::map<std::string, std::shared_ptr<Expression>>;
    
    Let(Bindings bindings_, std::unique_ptr<Expression> result_) :
        Expression(result_->getType()),
        bindings(std::move(bindings_)),
        result(std::move(result_))
    {}
    
    static ParseResult parse(const mbgl::style::conversion::Convertible&, ParsingContext);
    
    EvaluationResult evaluate(const EvaluationParameters& params) const override;
    void eachChild(const std::function<void(const Expression*)>&) const override;
    
    Expression* getResult() const {
        return result.get();
    }

private:
    Bindings bindings;
    std::unique_ptr<Expression> result;
};

class Var : public Expression {
public:
    Var(std::string name_, std::shared_ptr<Expression> value_) :
        Expression(value_->getType()),
        name(std::move(name_)),
        value(value_)
    {}

    static ParseResult parse(const mbgl::style::conversion::Convertible&, ParsingContext);

    EvaluationResult evaluate(const EvaluationParameters& params) const override;
    void eachChild(const std::function<void(const Expression*)>&) const override;

private:
    std::string name;
    std::shared_ptr<Expression> value;
};

} // namespace expression
} // namespace style
} // namespace mbgl
