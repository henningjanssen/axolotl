<?php

namespace axolotl\control;

abstract class PageControl{
  protected $vars;
  public function __construct(array $vars){
    $this->vars = $vars;
  }

  public abstract function execute(): void;
}
