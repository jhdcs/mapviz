/**
 * Copyright 2019 Hatchbed L.L.C.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 **/ 

#ifndef MAPVIZ_PLUGINS_POSE_PLUGIN_H_
#define MAPVIZ_PLUGINS_POSE_PLUGIN_H_

// Include mapviz_plugin.h first to ensure GL deps are included in the right order
#include <mapviz/mapviz_plugin.h>

#include <mapviz/map_canvas.h>
#include <mapviz_plugins/point_drawing_plugin.h>

// C++ standard libraries
#include <list>
#include <string>
#include <vector>

// QT libraries
#include <QGLWidget>
#include <QObject>
#include <QWidget>

// ROS libraries
#include <rclcpp/rclcpp.hpp>
#include <tf2/transform_datatypes.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <swri_transform_util/local_xy_util.h>

// QT autogenerated files
#include "ui_pose_config.h"

namespace mapviz_plugins
{
  class PosePlugin : public mapviz_plugins::PointDrawingPlugin
  {
    Q_OBJECT

   public:
    PosePlugin();
    virtual ~PosePlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown()
    {
    }

    void Draw(double x, double y, double scale);

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);

   protected:
    void PrintError(const std::string& message);
    void PrintInfo(const std::string& message);
    void PrintWarning(const std::string& message);

   protected Q_SLOTS:
    void SelectTopic();
    void TopicEdited();

   private:
    Ui::pose_config ui_;
    QWidget* config_widget_;

    std::string topic_;

    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    bool has_message_;

    void PoseCallback(const geometry_msgs::msg::PoseStamped::SharedPtr pose);
  };
}

#endif  // MAPVIZ_PLUGINS_POSE_PLUGIN_H_
