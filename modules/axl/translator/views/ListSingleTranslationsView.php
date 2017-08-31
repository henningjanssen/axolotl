<?hh // strict

class ListSingleTranslationsView extends PageView {
  public function __construct(
    Map<string, string> $strings
  ){
    parent::__construct(t("List Translations"));

    $items = <div />;
    foreach ($strings as $id => $string) {
      $items->appendChild(
      <bootstrap:panel>
        <bootstrap:panel:heading>{$id}</bootstrap:panel:heading>
        <bootstrap:panel:body>{$string}</bootstrap:panel:body>
      </bootstrap:panel>
      );
    }

    $this->content->appendChild($items);
  }
}
