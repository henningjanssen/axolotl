<?hh // strict

use axolotl\entities\Module;
use axolotl\util\_;

class InstallModuleView extends PageView{
  public function __construct(
    bool $attempt, ?Module $module
  ){
    parent::__construct("Install module");
    $baseuri = strval(_::SETTINGS("system.base_uri", ""));
    if($attempt){
      $msg = $module !== null
        ? "Modules successfully installed."
        : "There were errors installing the module.";
      $link = $module === null ? <x:frag/> :
        <a href={$baseuri.'/'.urlencode($module->getVendor())
            .'/'.urlencode($module->getName()).'/'}>
          Try it out!
        </a>;
      $this->content->appendChild(
        <bootstrap:alert use={$module !== null ? "success" : "danger"}>
          {$msg}{$link}
        </bootstrap:alert>
      );
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
