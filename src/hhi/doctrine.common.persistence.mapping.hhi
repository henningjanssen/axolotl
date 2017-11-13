<?hh // decl

namespace \Doctrine\Common\Persistence\Mapping;

interface ClassMetadata{
    public function getName(): string;
    public function getIdentifier(): array<string>;
    public function getReflectionClass(): \ReflectionClass;
    public function isIdentifier(string $fieldName): bool;
    public function hasField(string $fieldName): bool;
    public function hasAssociation(string $fieldName): bool;
    public function isSingleValuedAssociation(string $fieldName): bool;
    public function isCollectionValuedAssociation(string $fieldName): bool;
    public function getFieldNames(): array<arraykey, string>;
    public function getIdentifierFieldNames(): array<arraykey, string>;
    public function getAssociationNames(): array<arraykey, string>;
    public function getTypeOfField(string $fieldName): string;
    public function getAssociationTargetClass(string $assocName): string;
    public function isAssociationInverseSide(string $assocName): bool;
    public function getAssociationMappedByTargetField(string $assocName): string;
    public function getIdentifierValues(object $object): array<arraykey, mixed>;
}
