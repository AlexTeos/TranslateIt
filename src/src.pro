QT -= gui
QT += network core

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TelegramAPI/api.cpp \
    TelegramAPI/types/animation.cpp \
    TelegramAPI/types/audio.cpp \
    TelegramAPI/types/callbackgame.cpp \
    TelegramAPI/types/callbackquery.cpp \
    TelegramAPI/types/chat.cpp \
    TelegramAPI/types/chatinvitelink.cpp \
    TelegramAPI/types/chatjoinrequest.cpp \
    TelegramAPI/types/chatlocation.cpp \
    TelegramAPI/types/chatmember.cpp \
    TelegramAPI/types/chatmemberadministrator.cpp \
    TelegramAPI/types/chatmemberbanned.cpp \
    TelegramAPI/types/chatmemberleft.cpp \
    TelegramAPI/types/chatmembermember.cpp \
    TelegramAPI/types/chatmemberowner.cpp \
    TelegramAPI/types/chatmemberrestricted.cpp \
    TelegramAPI/types/chatmemberupdated.cpp \
    TelegramAPI/types/chatpermissions.cpp \
    TelegramAPI/types/chatphoto.cpp \
    TelegramAPI/types/choseninlineresult.cpp \
    TelegramAPI/types/common.cpp \
    TelegramAPI/types/contact.cpp \
    TelegramAPI/types/dice.cpp \
    TelegramAPI/types/document.cpp \
    TelegramAPI/types/encryptedcredentials.cpp \
    TelegramAPI/types/encryptedpassportelement.cpp \
    TelegramAPI/types/forcereply.cpp \
    TelegramAPI/types/game.cpp \
    TelegramAPI/types/inlinekeyboardbutton.cpp \
    TelegramAPI/types/inlinekeyboardmarkup.cpp \
    TelegramAPI/types/inlinequery.cpp \
    TelegramAPI/types/invoice.cpp \
    TelegramAPI/types/keyboardbutton.cpp \
    TelegramAPI/types/keyboardbuttonpolltype.cpp \
    TelegramAPI/types/location.cpp \
    TelegramAPI/types/loginurl.cpp \
    TelegramAPI/types/maskposition.cpp \
    TelegramAPI/types/message.cpp \
    TelegramAPI/types/messageautodeletetimerchanged.cpp \
    TelegramAPI/types/messageentity.cpp \
    TelegramAPI/types/orderinfo.cpp \
    TelegramAPI/types/passportdata.cpp \
    TelegramAPI/types/passportfile.cpp \
    TelegramAPI/types/photosize.cpp \
    TelegramAPI/types/poll.cpp \
    TelegramAPI/types/pollanswer.cpp \
    TelegramAPI/types/polloption.cpp \
    TelegramAPI/types/precheckoutquery.cpp \
    TelegramAPI/types/proximityalerttriggered.cpp \
    TelegramAPI/types/replykeyboardmarkup.cpp \
    TelegramAPI/types/replykeyboardremove.cpp \
    TelegramAPI/types/shippingaddress.cpp \
    TelegramAPI/types/shippingquery.cpp \
    TelegramAPI/types/sticker.cpp \
    TelegramAPI/types/successfulpayment.cpp \
    TelegramAPI/types/update.cpp \
    TelegramAPI/types/user.cpp \
    TelegramAPI/types/venue.cpp \
    TelegramAPI/types/video.cpp \
    TelegramAPI/types/videonote.cpp \
    TelegramAPI/types/voice.cpp \
    TelegramAPI/types/voicechatended.cpp \
    TelegramAPI/types/voicechatparticipantsinvited.cpp \
    TelegramAPI/types/voicechatscheduled.cpp \
    TelegramAPI/types/voicechatstarted.cpp \
        main.cpp \
    sentencestorage.cpp \
    translateitbot.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    TelegramAPI/api.h \
    TelegramAPI/types/animation.h \
    TelegramAPI/types/audio.h \
    TelegramAPI/types/callbackgame.h \
    TelegramAPI/types/callbackquery.h \
    TelegramAPI/types/chat.h \
    TelegramAPI/types/chatinvitelink.h \
    TelegramAPI/types/chatjoinrequest.h \
    TelegramAPI/types/chatlocation.h \
    TelegramAPI/types/chatmember.h \
    TelegramAPI/types/chatmemberadministrator.h \
    TelegramAPI/types/chatmemberbanned.h \
    TelegramAPI/types/chatmemberleft.h \
    TelegramAPI/types/chatmembermember.h \
    TelegramAPI/types/chatmemberowner.h \
    TelegramAPI/types/chatmemberrestricted.h \
    TelegramAPI/types/chatmemberupdated.h \
    TelegramAPI/types/chatpermissions.h \
    TelegramAPI/types/chatphoto.h \
    TelegramAPI/types/choseninlineresult.h \
    TelegramAPI/types/common.h \
    TelegramAPI/types/contact.h \
    TelegramAPI/types/dice.h \
    TelegramAPI/types/document.h \
    TelegramAPI/types/encryptedcredentials.h \
    TelegramAPI/types/encryptedpassportelement.h \
    TelegramAPI/types/forcereply.h \
    TelegramAPI/types/game.h \
    TelegramAPI/types/inlinekeyboardbutton.h \
    TelegramAPI/types/inlinekeyboardmarkup.h \
    TelegramAPI/types/inlinequery.h \
    TelegramAPI/types/invoice.h \
    TelegramAPI/types/keyboardbutton.h \
    TelegramAPI/types/keyboardbuttonpolltype.h \
    TelegramAPI/types/location.h \
    TelegramAPI/types/loginurl.h \
    TelegramAPI/types/maskposition.h \
    TelegramAPI/types/message.h \
    TelegramAPI/types/messageautodeletetimerchanged.h \
    TelegramAPI/types/messageentity.h \
    TelegramAPI/types/orderinfo.h \
    TelegramAPI/types/passportdata.h \
    TelegramAPI/types/passportfile.h \
    TelegramAPI/types/photosize.h \
    TelegramAPI/types/poll.h \
    TelegramAPI/types/pollanswer.h \
    TelegramAPI/types/polloption.h \
    TelegramAPI/types/precheckoutquery.h \
    TelegramAPI/types/proximityalerttriggered.h \
    TelegramAPI/types/replykeyboardmarkup.h \
    TelegramAPI/types/replykeyboardremove.h \
    TelegramAPI/types/shippingaddress.h \
    TelegramAPI/types/shippingquery.h \
    TelegramAPI/types/sticker.h \
    TelegramAPI/types/successfulpayment.h \
    TelegramAPI/types/update.h \
    TelegramAPI/types/user.h \
    TelegramAPI/types/venue.h \
    TelegramAPI/types/video.h \
    TelegramAPI/types/videonote.h \
    TelegramAPI/types/voice.h \
    TelegramAPI/types/voicechatended.h \
    TelegramAPI/types/voicechatparticipantsinvited.h \
    TelegramAPI/types/voicechatscheduled.h \
    TelegramAPI/types/voicechatstarted.h \
    common.h \
    sentencestorage.h \
    translateitbot.h
