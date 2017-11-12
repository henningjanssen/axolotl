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

namespace Doctrine\ORM\Tools{
  class SchemaTool{
    private \Doctrine\ORM\EntityManagerInterface $em;
    private \Doctrine\DBAL\Platforms\AbstractPlatform $platform;
    private \Doctrine\ORM\Mapping\QuoteStrategy $quoteStrategy;

    public function __construct(\Doctrine\ORM\EntityManagerInterface $em);
    public function createSchema(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes): void;
    public function getCreateSchemaSql(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes): string;
    private function processingNotRequired(\Doctrine\ORM\Mapping\ClassMetadata $class, array<\Doctrine\ORM\Mapping\ClassMetadata> $processedClasses): bool;
    public function getSchemaFromMetadata(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes): \Doctrine\DBAL\Schema\Schema;
    private function addDiscriminatorColumnDefinition(\Doctrine\ORM\Mapping\ClassMetadata $class, \Doctrine\DBAL\Schema\Table $table): void;
    private function gatherColumns(\Doctrine\ORM\Mapping\ClassMetadata $class, \Doctrine\DBAL\Schema\Table $table): void;
    private function gatherColumn(\Doctrine\ORM\Mapping\ClassMetadata $class, array<string, mixed> $mapping, \Doctrine\DBAL\Schema\Table $table): void;
    private function gatherRelationsSql(\Doctrine\ORM\Mapping\ClassMetadata $class, \Doctrine\DBAL\Schema\Table $table, \Doctrine\DBAL\Schema\Schema $schema, array<mixed> &$addedFks, array<mixed> &$blacklistedFks): void;
    private function getDefiningClass(\Doctrine\ORM\Mapping\ClassMetadata $class, string $referencedColumnName): array<mixed>;
    private function gatherRelationJoinColumns(array<mixed> $joinColumns, \Doctrine\DBAL\Schema\Table $theJoinTable, \Doctrine\ORM\Mapping\ClassMetadata $class, array<mixed> $mapping, array<mixed> &$primaryKeyColumns, array<mixed> &$addedFks, array<mixed> &$blacklistedFks): void;
    public function dropSchema(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes): void;
    public function dropDatabase(): void;
    public function getDropDatabaseSQL(): array<string>;
    public function getDropSchemaSQL(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes): array<string>;
    public function updateSchema(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes, bool $saveMode = false): void;
    public function getUpdateSchemaSql(array<\Doctrine\ORM\Mapping\ClassMetadata> $classes, bool $saveMode = false): array<string>;
  }
}
