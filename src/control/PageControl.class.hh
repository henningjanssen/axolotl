<?hh // strict

namespace axolotl\control;

abstract class PageControl{
  private array<string> $vars;
  public function __construct(array<string> $vars){
    $this->vars = $vars;
  }

  public abstract function execute(): void;
}
