#amixer cset name='PCM Playback Volume' 100%,100%
export FRAMEBUFFER=/dev/fb2
export QWS_DISPLAY=LinuxFB:/dev/fb2
export QT_QWS_FONTDIR=/usr/local/Trolltech/QtEmbedded-4.6.2-arm/lib/fonts
./client -qws


