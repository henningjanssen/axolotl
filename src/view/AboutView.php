<?php

namespace axolotl\view;

use \axolotl\util\_;
use \axolotl\util\AXLSettingsFile;

class AboutView extends PageView{
  public function __construct(
    //
  ){
    parent::__construct('about.html', "i18n:about.title");
    $vendorWebsite = strval(
      _::SETTINGS("vendor.website", "", _::SETTINGS_APP)
    );
    $this->setVars(array(
      'vendor' => _::SETTINGS("vendor", array(), _::SETTINGS_APP),
      'axl' => array(
        'version' => '0.0.0',
        'commit' => 'sha'
      )
    ));
  }
}
