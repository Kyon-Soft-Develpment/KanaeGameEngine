#include "Launcher.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#include <nfd.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <cstring>
#include <ctime>

using json = nlohmann::json;
namespace fs = std::filesystem;

// JSON serialization for Project struct
namespace nlohmann {
    template<>
    struct adl_serializer<Project> {
        static void to_json(json& j, const Project& p) {
            j = json{
                {"name", p.name},
                {"path", p.path},
                {"description", p.description},
                {"created_date", p.created_date},
                {"last_modified", p.last_modified}
            };
        }

        static void from_json(const json& j, Project& p) {
            j.at("name").get_to(p.name);
            j.at("path").get_to(p.path);
            j.at("description").get_to(p.description);
            j.at("created_date").get_to(p.created_date);
            j.at("last_modified").get_to(p.last_modified);
        }
    };
}

Launcher::Launcher()
    : m_window(nullptr)
    , m_selectedProject(-1)
    , m_showNewProjectDialog(false)
{
    std::cout << "Initializing Launcher..." << std::endl;
    initWindow();
    initVulkan();
    initImGui();
    loadProjects();
}

Launcher::~Launcher() {
    cleanup();
}

void Launcher::initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(1280, 720, "Kanae Game Engine Launcher", nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        auto launcher = reinterpret_cast<Launcher*>(glfwGetWindowUserPointer(window));
        launcher->handleResize(width, height);
    });
}

void Launcher::initVulkan() {
    m_vulkanContext.initialize("Kanae Game Engine Launcher");
}

void Launcher::handleResize(int width, int height) {
    if (width == 0 || height == 0) {
        return;
    }

    vkDeviceWaitIdle(m_vulkanContext.getDevice());
    // Note: createSwapchain is private, so we can't call it directly
    // The VulkanContext should handle resize internally
}

void Launcher::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForVulkan(m_window, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = m_vulkanContext.getInstance();
    init_info.PhysicalDevice = m_vulkanContext.getPhysicalDevice();
    init_info.Device = m_vulkanContext.getDevice();
    init_info.QueueFamily = m_vulkanContext.getGraphicsQueueFamily();
    init_info.Queue = m_vulkanContext.getGraphicsQueue();
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.DescriptorPool = m_vulkanContext.getDescriptorPool();
    init_info.MinImageCount = 2;
    init_info.ImageCount = m_vulkanContext.getSwapchainImageCount();
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Allocator = nullptr;
    init_info.CheckVkResultFn = nullptr;

    if (!ImGui_ImplVulkan_Init(&init_info, m_vulkanContext.getRenderPass())) {
        throw std::runtime_error("Failed to initialize ImGui Vulkan implementation");
    }
}

void Launcher::run() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderProjectList();
        renderProjectDetails();
        if (m_showNewProjectDialog) {
            renderNewProjectDialog();
        }

        ImGui::Render();

        if (m_vulkanContext.beginFrame()) {
            ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_vulkanContext.getCurrentCommandBuffer());
            m_vulkanContext.endFrame();
        }
    }

    vkDeviceWaitIdle(m_vulkanContext.getDevice());
}

void Launcher::cleanup() {
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_vulkanContext.cleanup();

    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

void Launcher::loadProjects() {
    try {
        std::ifstream file("projects.json");
        if (file.is_open()) {
            nlohmann::json j;
            file >> j;
            m_projects = j.get<std::vector<Project>>();
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load projects: " << e.what() << std::endl;
    }
}

void Launcher::saveProjects() {
    try {
        nlohmann::json j = m_projects;
        std::ofstream file("projects.json");
        file << j.dump(4);
    } catch (const std::exception& e) {
        std::cerr << "Failed to save projects: " << e.what() << std::endl;
    }
}

void Launcher::renderProjectList() {
    ImGui::Begin("Projects");
    
    if (ImGui::Button("New Project")) {
        m_showNewProjectDialog = true;
        m_newProject = Project();
    }

    ImGui::Separator();

    for (size_t i = 0; i < m_projects.size(); i++) {
        if (ImGui::Selectable(m_projects[i].name.c_str(), m_selectedProject == static_cast<int>(i))) {
            m_selectedProject = static_cast<int>(i);
        }
    }

    ImGui::End();
}

void Launcher::renderProjectDetails() {
    if (m_selectedProject >= 0 && m_selectedProject < static_cast<int>(m_projects.size())) {
        ImGui::Begin("Project Details");
        
        const Project& project = m_projects[m_selectedProject];
        ImGui::Text("Name: %s", project.name.c_str());
        ImGui::Text("Path: %s", project.path.c_str());
        ImGui::Text("Description: %s", project.description.c_str());
        ImGui::Text("Created: %s", project.created_date.c_str());
        ImGui::Text("Last Modified: %s", project.last_modified.c_str());

        if (ImGui::Button("Open Project")) {
            // TODO: Implement project opening
        }

        ImGui::End();
    }
}

void Launcher::renderNewProjectDialog() {
    ImGui::Begin("New Project", &m_showNewProjectDialog);

    static char name[256] = "";
    static char description[1024] = "";

    ImGui::InputText("Name", name, sizeof(name));
    ImGui::InputTextMultiline("Description", description, sizeof(description));

    if (ImGui::Button("Create")) {
        if (strlen(name) > 0) {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            std::string timestamp = std::ctime(&now_c);
            timestamp.pop_back(); // Remove trailing newline

            m_newProject.name = name;
            m_newProject.description = description;
            m_newProject.created_date = timestamp;
            m_newProject.last_modified = timestamp;
            m_newProject.path = getProjectFullPath(m_newProject);

            createNewProject(m_newProject);
            m_showNewProjectDialog = false;
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
        m_showNewProjectDialog = false;
    }

    ImGui::End();
}

std::string Launcher::getProjectFullPath(const Project& project) const {
    return std::filesystem::current_path().string() + "/Projects/" + project.name;
}

bool Launcher::createProjectDirectory(const Project& project) {
    std::string projectPath = getProjectFullPath(project);
    try {
        std::filesystem::create_directories(projectPath);
        std::filesystem::create_directories(projectPath + "/src");
        std::filesystem::create_directories(projectPath + "/assets");
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Failed to create project directories: " << e.what() << std::endl;
        return false;
    }
}

void Launcher::createProjectFiles(const Project& project) {
    std::string projectPath = getProjectFullPath(project);

    // Create project config file
    {
        nlohmann::json config;
        config["name"] = project.name;
        config["description"] = project.description;
        config["created_date"] = project.created_date;
        config["last_modified"] = project.last_modified;

        std::ofstream configFile(projectPath + "/project.json");
        configFile << config.dump(4);
    }

    // Create README.md
    {
        std::ofstream readmeFile(projectPath + "/README.md");
        readmeFile << "# " << project.name << "\n\n";
        readmeFile << project.description << "\n\n";
        readmeFile << "Created: " << project.created_date << "\n";
        readmeFile << "Last Modified: " << project.last_modified << "\n";
    }
}

void Launcher::createNewProject(const Project& project) {
    if (createProjectDirectory(project)) {
        createProjectFiles(project);
        m_projects.push_back(project);
        saveProjects();
    }
} 