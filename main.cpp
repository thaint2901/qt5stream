#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include <QApplication>
#include <QTimer>
#include <QVideoWidget>

#include "widget.h"

int main(int argc, char *argv[])
{
  gst_init(&argc, &argv);
  QApplication app(argc, argv);
  app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

  // prepare the pipeline

  GError *error = NULL;
  GstElement* pipeline = gst_parse_launch("shmsrc socket-path=/tmp/tmpsock ! \
    video/x-raw, format=(string)I420,  width=(int)1280, height=(int)720, framerate=(fraction)30/1 ! \
    xvimagesink sync=false name=sink", &error);
  // auto sink = gst_bin_get_by_interface(GST_BIN(pipeline), GST_TYPE_VIDEO_OVERLAY);
  GstElement* sink = gst_bin_get_by_name((GstBin*) pipeline, "sink");

  // prepare the ui

  auto videoWidget = new QVideoWidget;
  videoWidget->setWindowState(Qt::WindowFullScreen);
  videoWidget->show();

  WId xwinid = videoWidget->winId();
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink), xwinid);

  GstStateChangeReturn sret = gst_element_set_state(pipeline,
                                                    GST_STATE_PLAYING);
  if (sret == GST_STATE_CHANGE_FAILURE)
  {
    g_print("Failllllllllllll\n");
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    // Exit application
    QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
  }

  auto widget = new Widget();
  widget->show();
  widget->setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));

  int ret = app.exec();

  videoWidget->hide();
  delete videoWidget;
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);

  return ret;
}