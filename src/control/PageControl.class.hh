<?hh // strict

namespace axolotl\control;

abstract class PageControl{
  protected array<string, string> $vars;
  public function __construct(array<string, string> $vars){
    $this->vars = $vars;
  }

  public abstract function execute(): void;
}
