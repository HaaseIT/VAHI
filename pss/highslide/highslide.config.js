/**
*	Site-specific configuration settings for Highslide JS
*/
hs.graphicsDir = '/pss/highslide/graphics/';
hs.showCredits = false;
hs.outlineType = 'custom';
hs.dimmingOpacity = 0.8;
hs.fadeInOut = false;
hs.align = 'center';
hs.allowMultipleInstances = false;
hs.captionEval = 'this.a.title';
hs.registerOverlay({
	html: '<div class="closebutton" onclick="return hs.close(this)" title="Schließen"></div>',
	position: 'top right',
	useOnHtml: true,
	fade: 2 // fading the semi-transparent overlay looks bad in IE
});



// Add the slideshow controller
hs.addSlideshow({
	slideshowGroup: 'group1',
	interval: 5000,
	repeat: true,
	useControls: true,
	fixedControls: 'fit',
	overlayOptions: {
		opacity: '0.6',
		position: 'bottom center',
		offsetX: '0',
		offsetY: '-10',
		hideOnMouseOut: true
	}
});

// German language strings
hs.lang = {
	cssDirection: 'ltr',
	loadingText: 'Lade...',
	loadingTitle: 'Klick zum Abbrechen',
	focusTitle: 'Klick um nach vorn zu bringen',
	fullExpandTitle: 'Zur Originalgr&ouml;&szlig;e erweitern',
	creditsText: 'Powered by <i>Highslide JS</i>',
	creditsTitle: 'Gehe zur Highslide JS Homepage',
	previousText: 'Voriges',
	nextText: 'Nächstes',
	moveText: 'Verschieben',
	closeText: 'Schließen',
	closeTitle: 'Schließen (Esc)',
	resizeTitle: 'Größe wiederherstellen',
	playText: 'Abspielen',
	playTitle: 'Slideshow abspielen (Leertaste)',
	pauseText: 'Pause',
	pauseTitle: 'Pausiere Slideshow (Leertaste)',
	previousTitle: 'Voriges (Pfeiltaste links)',
	nextTitle: 'Nächstes (Pfeiltaste rechts)',
	moveTitle: 'Verschieben',
	fullExpandText: 'Vollbild',
	number: 'Bild %1 von %2',
	restoreTitle: 'Klick um das Bild zu schließen, klick und ziehe um zu verschieben. Benutze Pfeiltasten für vor und zurück.'
};

// gallery config object
var config1 = {
	slideshowGroup: 'group1',
	transitions: ['expand', 'crossfade']
};
