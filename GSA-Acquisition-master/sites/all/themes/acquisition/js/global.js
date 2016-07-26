jQuery(function ($) {
    jQuery(document).ready( function() {


        /* Mobile menu initialization */
        $('#mobile-menu').mmenu({
           "extensions": [
              "effect-menu-zoom",
              "pagedim-black"
           ]
        });

        /*landing page carousel*/
        $('#landing-slider').slick({
            dots:           true,
            speed:          800,
            autoplaySpeed:  3000,
            autoplay:       true,
            dotsClass:      'landing-slider-dots',
            prevArrow:      '<button type="button" class="slick-prev custom-prev">Previous</button>',
            nextArrow:      '<button type="button" class="slick-next custom-next">Next</button>'
        });
        if ($('body').hasClass('front')){
            /*Video Gallery*/
            var sourceURL = $('.views-field-field-video-embed-video-url .field-content').get(0).innerHTML;
            var firstVidThumb = $('.vid-tn-col').get(0);
            var firstVidDesc = $(firstVidThumb).find('.video-embed-description').text();
            var firstVidTitle = $(firstVidThumb).find('.views-field-title > .field-content').text();
            var parentGallery = $('#video-highlights');

            /*Initial load of content*/
            parentGallery.find('#vid-desc > h2').text(firstVidTitle);
            parentGallery.find('#vid-desc > p').text(firstVidDesc);
            $('.vid-tn-wrapper').before('<iframe width="357" height="207" src="' + sourceURL + '" frameborder="0" allowfullscreen></iframe>');

            /*Changes video on click*/
            $('.vid-tn-col').click(function(e){
                e.preventDefault();
                $this = $(this);
                var vidThumbGalleryTitle = $this.find('.views-field-title').children('span').text();
                var vidThumbGalleryDesc  = $this.find('.video-embed-description').text();

                /*Replaces URL with what is clicked*/
                sourceURL = $this.find('div.views-field-field-video-embed-video-url').children('div').text();
                $('#video-highlights > iframe').attr('src',sourceURL);

                /*updates main title and description*/
                parentGallery.find('#vid-desc > h2').text(vidThumbGalleryTitle);
                parentGallery.find('#vid-desc > p').text(vidThumbGalleryDesc);
            });
        }
        if($('body').hasClass('page-search')){

            // Checkbox styling solution for search results page

            $('.page-search .block-facetapi input[type=checkbox], #advanced-search-type input[type=checkbox]').each(function() {
                var span = $('<span class="' + $(this).attr('type') + ' ' + $(this).attr('class') + '"></span>').click(doCheck);
                if ($(this).is(':checked')) {
                    span.addClass('checked');
                }
                $(this).wrap(span).addClass('hide_it');
            });
            function doCheck() {
                if ($(this).hasClass('checked')) {
                    $(this).removeClass('checked');
                    $(this).children().prop("checked", false);
                } else {
                    $(this).addClass('checked');
                    $(this).children().prop("checked", true);
                }
            }
//            var mySplit = $('.filter-sidebar a.facetapi-checkbox').each(function(){
//                $(this).get($(this).text().split('(', ')'));
//            });
//         console.log(mySplit);
        }
        if($('body').is('.page-gsam-archives, .page-far-archives, .page-far-looseleaf, .page-gsam-looseleaf')){
            $('#edit-title-wrapper').after('<p>OR</p>');
//            $('#edit-submit-archives').on('submit', function(){
//                window.setTimeout(addOr, 500);
//                function addOr(){
//                    $('#edit-title-wrapper').after('<p>OR</p>');
//                }
//            });
            /*Adds the 'OR' after AJAX is fired and content is loaded*/
            Drupal.behaviors.loadAfterAjax = {
                attach: function() {
                    $('#edit-title-wrapper').once().after('<p>OR</p>');
                }
            }
        };
    });
});
