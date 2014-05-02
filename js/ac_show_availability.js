(function ($) {
// Store our function as a property of Drupal.behaviors.
Drupal.behaviors.acsaSlider = {
  attach: function (context, settings) {
    var $slidewidth = Drupal.settings.acsa.acsa_slidewidth;
    var $minslides = Drupal.settings.acsa.acsa_minslides;
    var $maxslides = Drupal.settings.acsa.acsa_maxslides;
    var $slidemargin = Drupal.settings.acsa.acsa_slidemargin;
    $('.slider1').bxSlider({
      slideWidth: $slidewidth,
      minSlides: $minslides,
      maxSlides: $maxslides,
      slideMargin: $slidemargin,
      pager: false,
      infiniteLoop: false
    });
  }
};
}(jQuery));