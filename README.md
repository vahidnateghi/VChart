# VChart
QT Chart Library using OpenGL!

This library is a Chart library for QT with the help of OpenGL library to show charts with minimum performance required. The focus on these charts is the performance.
This library doesn't have any dependencies and you can use them in almost any QT project.


# Download
Download the .pri project from github: github.com/vahidnateghi/VChart

# How to use
Add the .pri project to your project. In designer add a QWidget to your form and promote it to one of the chart classes provided. In each category there is a class with no numbers at the end of its name, that is the base class for that category, promote your widgets to the classes with numbers at the end...

# General Properties
Generally every chart has it's points categorised as CHANNELS. In every chart there can be multiple channels showing different groups of data. Channel type for each chart type is different. 
Every type of chart can be zoomed in and out and the zoom can be reset. By doing each of these actions, signals will be triggered acordingly. 
