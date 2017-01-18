<?hh // strict

namespace axolotl\control;

abstract class PageControl{
  protected Map<string, string> $vars;
  public function __construct(Map<string, string> $vars){
    $this->vars = $vars;
  }

  public abstract function execute(): void;
}
