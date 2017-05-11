<?hh // strict

use axolotl\entities\Module;
use axolotl\util\_;

class InstallModuleView extends PageView{
  public function __construct(
    bool $attempt, array<Module> $modules, array<string> $errors = array()
  ){
    parent::__construct("Install module");
    $baseuri = strval(_::SETTINGS("system.base_uri", ""));
    if($attempt){
      $msg = count($errors) == 0
        ? "Modules successfully installed."
        : "There were errors installing the module.<br/>"
          .implode("<br/>", $errors);
      $modLinks = count($modules) === 0 ? <x:frag/>
        : <bootstrap:list-group/>;
      if(count($modules) > 0){
        foreach($modules as $m){
          $url = '/m/'.urlencode(strtolower($m->getVendor()))
            .'/'.urlencode(strtolower($m->getName())).'/';
          $modLinks->appendChild(
            <bootstrap:list-group-item href={$url}>
              {$m->getName()}
            </bootstrap:list-group-item>
          );
        }
      }
      $this->content->appendChild(
        <bootstrap:alert use={count($errors) === 0 ? "success" : "danger"}>
          {$msg}
        </bootstrap:alert>
      );
      $this->content->appendChild($modLinks);
    }
    $this->content->appendChild(
      <bootstrap:panel>
        <bootstrap:panel:heading>
          Install new module!
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <form action={$baseuri.'/settings/modules/install'} method="post"
            enctype="multipart/form-data"
          >
            <div class="form-group">
              <label for="__ax_modFile">.zip containing the module</label>
              <fileupload id="__ax_modFile" name="__ax_modFile"
                accept="zip"/>
              <small id="modFileDesc" class="form-text text-muted">
                For more information about modules take a look at the
                project on github.
              </small>
            </div>
            <button type="submit" class="btn btn-primary" style="float:right;">
              Install!
            </button>
          </form>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
  }
}
