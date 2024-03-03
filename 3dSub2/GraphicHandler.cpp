#include "GraphicHandler.h"
#include <d3d11.h>  // Include DirectX header
//The beginning of initialising DirectX, I hope...


// Define VertexType struct
struct VertexType
{
    float x, y, z; // Example: replace with your actual vertex components
};

// Define a simple LoadShader function (replace it with your actual shader loading logic)
ID3DBlob* LoadShader(const char* shaderCode, const char* entryPoint, const char* shaderModel)
{
    // Implementation for loading shader code and creating shader blob
    // Replace this with your actual shader loading code
    return nullptr; // Replace with actual implementation
}

GraphicHandler::GraphicHandler(HWND hwnd, UINT width, UINT height) : hwnd(hwnd), screenWidth(width), screenHeight(height)
{
    // Initialize Direct3D and create necessary resources
    if (!InitializeDirect3D())
    {
        std::cerr << "Failed to initialize Direct3D!" << std::endl;
        exit(-1);
    }

    // Might need to, create additional resources (vertex buffers, index buffers, shaders, etc.)
    CreateResources();
}

GraphicHandler::~GraphicHandler()
{
    // Release resources and clean like a biatch
    ReleaseResources();
    // Comented out cuz tried to make it work cuz shit aint woking
    // CleanupDirect3D(); 
}

bool GraphicHandler::InitializeDirect3D()
{
    // Create a swap chain description
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = screenWidth;
    swapChainDesc.BufferDesc.Height = screenHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    // Create the Direct3D device and swap chain
    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    if (FAILED(result))
    {
        // Handle initialization failure
        // Log an error message or display an error dialog
        std::cerr << "Failed to create Direct3D device and swap chain!" << std::endl;
        return false;
    }

    // Assuming I need to have a back buffer (swapChainBuffer)
    // comented out HRESULT, one page said it is nice on said it is stupid and Im trying
    /*HRESULT*/ result = swapChain->GetBuffer(0, IID_PPV_ARGS(&swapChainBuffer));
    if (FAILED(result))
    {
        std::cerr << "Failed to get the swap chain buffer!" << std::endl;
        return false;
    }

    result = device->CreateRenderTargetView(swapChainBuffer.Get(), nullptr, &renderTargetView);
    if (FAILED(result))
    {
        std::cerr << "Failed to create the render target view!" << std::endl;
        return false;
    }

    return true;
}

void GraphicHandler::CreateResources()
{
    // Defining verticles in separate function or vertex buffer object
    // Do not know which i need but internet says simple vertex buffer is most worth
    VertexType vertices[] = {
        // example vertext, said to add my numbers but i do not know them
        { 0.0f, 0.0f, 0.0f },
    };
    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * std::size(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &initData, &vertexBuffer);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create vertex buffer!" << std::endl;
        // Handle error appropriately
    }

    // This assumes you have the shader source code in a file or a string
    // Replace "ShaderCodeHere" with the actual shader code
    const char* vertexShaderCode = "ShaderCodeHere";

    D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
        // Define your input layout here
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    // Compile the shader (you need to implement LoadShader function)
    ID3DBlob* vertexShaderBlob = LoadShader(vertexShaderCode, "vs_main", "vs_5_0");

    hr = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create vertex shader!" << std::endl;
        // Handle error appropriately
    }

    hr = device->CreateInputLayout(layoutDesc, std::size(layoutDesc), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create input layout!" << std::endl;
        // Handle error appropriately
    }

    // Don't forget to release the shader blob after creating the shaders
    vertexShaderBlob->Release();
}

void GraphicHandler::ReleaseResources()
{
    // Release vertex buffer
    if (vertexBuffer)
    {
        vertexBuffer->Release();
        vertexBuffer = nullptr;
    }

    // Release shaders and input layout
    if (vertexShader)
    {
        vertexShader->Release();
        vertexShader = nullptr;
    }

    if (inputLayout)
    {
        inputLayout->Release();
        inputLayout = nullptr;
    }

    // Release render target view
    if (renderTargetView)
    {
        renderTargetView->Release();
        renderTargetView = nullptr;
    }

    // Release swap chain buffer
    if (swapChainBuffer)
    {
        swapChainBuffer->Release();
        swapChainBuffer = nullptr;
    }

    // Releases other resources as needed
}

void GraphicHandler::RenderFrame()
{
    // Clearing the render target, (with a black color?)
    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);

    // Set the vertex buffer, input layout, and vertex shader
    // Should be specific to my data, but dont know hjow and why so lets wing it
    UINT stride = sizeof(VertexType);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);

    // Set other rendering states (e.g., rasterizer state, depth-stencil state, blend state)

    // Draw call
    //Edit the number of verticles, dont know if this is hardcoding and bad or smart or smtn...
    deviceContext->Draw(/* Number of vertices */std::size(vertices), 0);

    // Frame present
    // Should be easy, and specific again weird im lost
    swapChain->Present(1, 0);
}
