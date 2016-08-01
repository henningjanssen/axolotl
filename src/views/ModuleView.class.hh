<?hh // strict

use axolotl\entities\Module;

class ModuleView extends PageView{
  public function __construct(
    array<Module> $modules
  ){
    parent::__construct("Modules");
    $moduleList = <bootstrap:list-group>
      </bootstrap:list-group>;
    foreach($modules as $m){
      $url = '/mdetails/'.urlencode($m->getVendor())
        .'/'.urlencode($m->getName()).'/';
      $moduleList->appendChild(
        <bootstrap:list-group-item href={$url}>
          <h4>{$m->getName()}</h4>
          <p>{$m->getDescription()}</p>
        </bootstrap:list-group-item>
      );
    }
    if(count($modules) === 0){
      $moduleList->appendChild(
        <bootstrap:list-group-item>
          No modules installed
        </bootstrap:list-group-item>
      );
    }
    $this->content->appendChild(<bootstrap:panel use="info">
        <bootstrap:panel:heading>
          Installed modules
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          {$moduleList}
        </bootstrap:panel:body>
      </bootstrap:panel>);
  }
}
