<?hh // decl
/*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* This software consists of voluntary contributions made by many individuals
* and is licensed under the MIT license. For more information, see
* <http://www.doctrine-project.org>.
*/

namespace Doctrine\Common\Collections\Expr
{

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class ClosureExpressionVisitor<T> extends ExpressionVisitor<T>
    {
        public static function getObjectFieldValue(object $object, string $field): T;
        public static function sortByField(string $name, int $orientation = 1, ?\Closure $next = null): \Closure;
        public function walkComparison(Comparison $comparison): T;
        public function walkValue(Value $value): T;
        public function walkCompositeExpression(CompositeExpression $expr): T;
        private function andExpressions(array<T> $expressions): (function(T): bool);
        private function orExpressions(array<T> $expressions): (function(T): bool);
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class Comparison<T> implements Expression<T>
    {
        const string EQ           = '=';
        const string NEQ          = '<>';
        const string LT           = '<';
        const string LTE          = '<=';
        const string GT           = '>';
        const string GTE          = '>=';
        const string IS           = '=';
        const string IN           = 'IN';
        const string NIN          = 'NIN';
        const string CONTAINS     = 'CONTAINS';
        const string MEMBER_OF    = 'MEMBER_OF';
        const string STARTS_WITH  = 'STARTS_WITH';
        const string ENDS_WITH    = 'ENDS_WITH';
        private string $field;
        private string $op;
        private Value $value;
        public function __construct(string $field, string $operator, T $value);
        public function getField(): string;
        public function getValue(): Value;
        public function getOperator(): string;
        public function visit(ExpressionVisitor $visitor): T;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class CompositeExpression<T> implements Expression<T>
    {
        const string TYPE_AND = 'AND';
        const string TYPE_OR  = 'OR';
        private string $type;
        private array<Expression> $expressions;
        public function __construct(string $type, array<Expression> $expressions);
        public function getExpressionList(): array<Expression>;
        public function getType(): string;
        public function visit(ExpressionVisitor $visitor): T;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    interface Expression<T>
    {
        public function visit(ExpressionVisitor $visitor): T;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    abstract class ExpressionVisitor<T>
    {
        abstract public function walkComparison(Comparison $comparison): T;
        abstract public function walkValue(Value $value): T;
        abstract public function walkCompositeExpression(CompositeExpression $expr): T;
        public function dispatch(Expression $expr): T;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class Value<T> implements Expression<T>
    {
        private T $value;
        public function __construct(T $value);
        public function getValue(): T;
        public function visit(ExpressionVisitor $visitor): T;
    }
}
