#pragma once

#include "../Graphics/VulkanContext.h"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Project {
    std::string name;
    std::string path;
    std::string description;
    std::string created_date;
    std::string last_modified;
};

class Launcher {
public:
    Launcher();
    ~Launcher();

    void run();

private:
    void initWindow();
    void initVulkan();
    void initImGui();
    void mainLoop();
    void cleanup();
    void handleResize(int width, int height);
    
    // Project management
    std::string getProjectFullPath(const Project& project) const;
    bool createProjectDirectory(const Project& project);
    void createProjectFiles(const Project& project);
    void createNewProject(const Project& project);
    void loadProjects();
    void saveProjects();
    void renderProjectList();
    void renderProjectDetails();
    void renderNewProjectDialog();

    GLFWwindow* m_window;
    Kanae::VulkanContext m_vulkanContext;
    std::vector<Project> m_projects;
    bool m_showNewProjectDialog;
    Project m_newProject;
    int m_selectedProject;
}; 