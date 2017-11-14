<?hh // strict

use axolotl\util\_;
use axolotl\util\AXLSettingsFile;
use axolotl\util\Session;

abstract class PageView extends View{
  protected :xhp $head;
  protected :xhp $content;
  protected :xhp $postcontent; //footer, etc.
  protected :xhp $modulenav;
  protected string $baseuri;

  public function __construct(string $title = ""){
    $vendor = strval(
      _::SETTINGS("system.title", "axolotl", AXLSettingsFile::APP)
    );
    if(strlen($title) > 0 && strlen($vendor) > 0){
      $title .= " | ";
    }
    if(strlen($vendor) > 0){
      $title .= $vendor;
    }
    $this->baseuri = strval(_::SETTINGS("system.base_uri", ""));
    $this->head =
      <head>
        <meta charset="utf-8"/>
        <meta name="robots" content="noindex,nofollow"/>
        <title>{$title}</title>
        <script src="//code.jquery.com/jquery-1.11.0.min.js"></script>
        <link
          rel="stylesheet"
          href="//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css"
        />
        <script src="//code.jquery.com/jquery-1.11.0.min.js"/>
        <script
          src="//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"
        />
        <!-- stuff for fileuploads -->
        <script src={"{$this->baseuri}/static/3rd-party/resumable.js"}/>
        <script src={"{$this->baseuri}/static/js/fileupload.js"}/>
      </head>;
    $this->modulenav = <x:frag/>;
    $this->content = <x:frag/>;
    $this->postcontent = <x:frag/>;
  }

  final protected function setModuleNavigation(array<string, string> $navs): void{
    if(count($navs) === 0){
      return;
    }
    $modulesubnav = <bootstrap:dropdown:menu>
        </bootstrap:dropdown:menu>;
    foreach($navs as $name => $url){
      $modulesubnav->appendChild(
        <bootstrap:dropdown:item
          href={$this->baseuri.$url}
        >
          <a href={$this->baseuri.$url}>{$name}</a>
        </bootstrap:dropdown:item>
      );
    }
    $this->modulenav = <bootstrap:navigation:dropdown>
      <a href="#">{'This Module'}<bootstrap:caret/></a>
      {$modulesubnav}
    </bootstrap:navigation:dropdown>;
  }

  final private function getPrecontent(): :xhp{
    $navbar =
      <bootstrap:navbar>
        <bootstrap:navbar:brand href="#">
          AXL
        </bootstrap:navbar:brand>
      </bootstrap:navbar>;

    if(Session::loggedIn()){
      $navbar->appendChild(
        <x:frag>
          <bootstrap:navigation:link href={$this->baseuri.'/home'}>
            {t('Home')}
          </bootstrap:navigation:link>
          {$this->modulenav}
          <bootstrap:navigation:link href={$this->baseuri.'/about'}>
            {t('About')}
          </bootstrap:navigation:link>
          <bootstrap:navigation:dropdown>
            <a href="#">
              {t('Settings')}
              <bootstrap:caret/>
            </a>
            <bootstrap:dropdown:menu>
              <bootstrap:dropdown:item
                href={$this->baseuri.'/settings/modules'}
              >
                <!--//Normally not needed. Bug in xhp-bootstrap, which
                //is also present on their docs
                //Does produce slightly different layout (space above entry)-->
                <a href={$this->baseuri.'/settings/modules'}>Modules</a>
              </bootstrap:dropdown:item>
            </bootstrap:dropdown:menu>
          </bootstrap:navigation:dropdown>
          <bootstrap:navigation:link href={$this->baseuri.'/logout'}>
            {t('Logout')}
          </bootstrap:navigation:link>
        </x:frag>
      );
    }
    else{
      $navbar->appendChild(
        <bootstrap:navigation:link href={$this->baseuri.'/login'}>
          {t('Login')}
        </bootstrap:navigation:link>
      );
    }
    return $navbar;
  }

  final public function render(): void{
    print(
      <x:doctype>
        <html>
          {$this->head}
          <body>
            {$this->getPrecontent()}
            {$this->content}
            {$this->postcontent}
          </body>
        </html>
      </x:doctype>
    );
  }
}
