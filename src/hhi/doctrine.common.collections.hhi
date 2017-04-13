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

namespace Doctrine\Common\Collections
{

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    abstract class AbstractLazyCollection<T> implements \Doctrine\Common\Collections\Collection<T>
    {
        protected ?Collection $collection;
        protected bool $initialized = false;

        public function isInitialized(): bool;
        protected function initialize(): void;
        abstract protected function doInitialize(): void;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class ArrayCollection<T> implements \Doctrine\Common\Collections\Collection<T>, Selectable
    {
        private array<T> $elements;
        public function __construct(array<T> $elements);
        protected function createFrom(array<T> $elements): this;
        public function __toString(): string;
        public function add(T $element): bool;
        public function matching(Criteria $criteria): Collection;
        public function getIterator(): ArrayIterator;
        public function clear(): void;
        public function contains(T $element): bool;
        public function isEmpty(): bool;
        public function remove(arraykey $key): T;
        public function removeElement(T $element): bool;
        public function containsKey(arraykey $key): bool;
        public function get(arraykey $key): T;
        public function getKeys(): array<arraykey>;
        public function getValues(): array<T>;
        public function set(arraykey $key, T $value): void;
        public function toArray(): array<T>;
        public function first(): T;
        public function last(): T;
        public function key(): arraykey;
        public function current(): T;
        public function next(): arraykey;
        public function exists(Closure $p): bool;
        public function filter(Closure $p): Collection;
        public function forAll(Closure $p): bool;
        public function map(Closure $func): this;
        public function partition(Closure $p): array<T>;
        public function indexOf(T $element): arraykey;
        public function slice(int $offset, ?int $length): array<T>;

        public function count(): int;
        public function offsetExists(arraykey $n): bool;
        public function offsetGet(arraykey $n): T;
        public function offsetSet(arraykey $n, T $element): void;
        public function offsetUnset(arraykey $n): void;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    interface Collection<T> extends \Countable, \IteratorAggregate<T>, \ArrayAccess<arraykey, T>
    {
        public function add(T $element): bool;
        public function clear(): void;
        public function contains(T $element): bool;
        public function isEmpty(): bool;
        public function remove(arraykey $key): T;
        public function removeElement(T $element): bool;
        public function containsKey(arraykey $key): bool;
        public function get(arraykey $key): T;
        public function getKeys(): array<arraykey>;
        public function getValues(): array<T>;
        public function set(arraykey $key, T $value): void;
        public function toArray(): array<T>;
        public function first(): T;
        public function last(): T;
        public function key(): arraykey;
        public function current(): T;
        public function next(): arraykey;
        public function exists(Closure $p): bool;
        public function filter(Closure $p): Collection;
        public function forAll(Closure $p): bool;
        public function map(Closure $func): this;
        public function partition(Closure $p): array<T>;
        public function indexOf(T $element): arraykey;
        public function slice(int $offset, ?int $length): array<T>;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class Criteria
    {
        const string ASC  = 'ASC';
        const string DESC = 'DESC';
        private static ?ExpressionBuilder $expressionBuilder;
        private ?Expr\Expression $expression;
        private array<string> $orderings = array();
        private ?int $firstResult;
        private ?int $maxResults;

        public static function create(): this;
        public static function expr(): ExpressionBuilder;
        public function __construct(
            ?Expr\Expression $expression = null,
            ?array<string> $orderings = null,
            ?int $firstResult = null,
            ?int $maxResults = null
        );
        public function where(Expr\Expression $expression): this;
        public function andWhere(Expr\Expression $expression): this;
        public function orWhere(Expr\Expression $expression): this;
        public function getWhereExpression(): ?Expr\Expression;
        public function getOrderings(): array<string>;
        public function orderBy(array<string> $orderings): this;
        public function getFirstResult(): ?int;
        public function setFirstResult(?int $firstResult): this;
        public function getMaxResults(): ?int;
        public function setMaxResults(?int $maxResults): this;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    class ExpressionBuilder<T>
    {
        public function andX(?T $x = null): Expr\CompositeExpression;
        public function orX(?T $x = null): Expr\CompositeExpression;
        public function eq(string $field, ?T $value): Expr\Comparison;
        public function gt(string $field, ?T $value): Expr\Comparison;
        public function lt(string $field, ?T $value): Expr\Comparison;
        public function gte(string $field, ?T $value): Expr\Comparison;
        public function lte(string $field, ?T $value): Expr\Comparison;
        public function neq(string $field, ?T $value): Expr\Comparison;
        public function isNull(string $field): Expr\Comparison;
        public function in(string $field, array<T> $values): Expr\Comparison;
        public function notIn(string $field, array<T> $values): Expr\Comparison;
        public function contains(string $field, T $value): Expr\Comparison;
        public function memberOf (string $field, T $value): Expr\Comparison;
        public function startsWith(string $field, T $value): Expr\Comparison;
        public function endsWith(string $field, T $value): Expr\Expression;
    }

    /*
    * @author Henning Janßen <development@henning-janssen.net>
    */
    interface Selectable
    {
        public function matching(Criteria $criteria): Collection;
    }
}
