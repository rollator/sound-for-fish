import QtQuick 2.0
import Sailfish.Silica 1.0
//import com.saildev.components 1.0

Page {
    id: searchPage
    property string searchString
    property bool keepSearchFieldFocus
    onSearchStringChanged: {
        streamy.search(searchString)
    }
    Component.onCompleted: listModel.update()
    Connections {
        target: streamy
        onSearchDone: {
            listModel.update()
        }
    }
    Loader {
        anchors.fill: parent
        sourceComponent: listViewComponent
    }

    Column {
        id: headerContainer

        width: searchPage.width

        PageHeader {
            title: "Search On Soundcloud"
        }

        SearchField {
            id: searchField
            width: parent.width


            Binding {
                target: searchPage
                property: "searchString"
                value: searchField.text.toLowerCase().trim()
            }
        }
    }

    Component {
        id: listViewComponent
        SilicaListView {
            model: listModel
            anchors.fill: parent
            currentIndex: -1 // otherwise currentItem will steal focus
            header:  Item {
                id: header
                width: headerContainer.width
                height: headerContainer.height
                Component.onCompleted: headerContainer.parent = header
            }

            PullDownMenu {
                MenuItem {
                    text: qsTr("meh; placeholder")
                }
            }
            delegate: ListItem {
                id: listItem
                menu: contextMenuComponent
                onClicked: streamy.playSearchItem(index)

                ListView.onAdd: AddAnimation {
                    target: listItem
                }
                ListView.onRemove: RemoveAnimation {
                    target: listItem
                }
                Label {
                    x: searchField.textLeftMargin
                    anchors.verticalCenter: parent.verticalCenter
                    color: searchString.length > 0 ? (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
                                                   : (highlighted ? Theme.highlightColor : Theme.primaryColor)
                    textFormat: Text.StyledText
                    text: Theme.highlightText(model.text, searchString, Theme.highlightColor)
                }
                Component {
                    id: contextMenuComponent
                    ContextMenu {
                        MenuItem {
                            text: qsTr("add to Playlist")
                            onClicked: streamy.addQueueSearchItem(index)
                        }
                    }
                }
            }

            VerticalScrollDecorator {}

            Component.onCompleted: {
                if (keepSearchFieldFocus) {
                    searchField.forceActiveFocus()
                }
                keepSearchFieldFocus = false
            }
        }
    }

    ListModel {
        id: listModel
        function update() {
            var tracks = streamy.tracks()
            listModel.clear()
            if(tracks.size == 0){
                return
            }

            for(var index = 0; index < tracks.length; index++){
                append({"text": tracks[index]})
            }
        }
    }
}
