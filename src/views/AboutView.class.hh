<?hh // strict

use \axolotl\util\_;

class AboutView extends PageView{
  public function __construct(
    //
  ){
    parent::__construct("About");
    $vendorWebsite = strval(_::SETTINGS("vendor_website", ""));
    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          Vendor
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              Vendor: {_::SETTINGS("vendor_name", "")}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Support E-Mail: {_::SETTINGS("vendor_mail", "")}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Support Phone: {_::SETTINGS("vendor_phone", "")}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item href={$vendorWebsite} target="_blank">
              Website: {$vendorWebsite}
            </bootstrap:list-group-item>
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          About this project
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              Project-Name: axolotl
            </bootstrap:list-group-item>
            <bootstrap:list-group-item
              href="http://github.com/henningjanssen/axolotl" target="_blank"
            >
              Project on Github: http://github.com/henningjanssen/axolotl
            </bootstrap:list-group-item>
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
  }
}
