<?hh // strict

class ListTranslationsView extends PageView {
  public function __construct(
    array<string> $locales
  ){
    parent::__construct(t("List Translations"));

    $items = <bootstrap:list-group />;
    foreach ($locales as $locale) {
      $items->appendChild(
        <bootstrap:list-group-item>
          {$locale}
        </bootstrap:list-group-item>
      );
    }

    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          {t('Existing Translations')}
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
            {$items}
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
  }
}