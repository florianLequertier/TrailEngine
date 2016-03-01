
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <deque>

using namespace glimac;


//////////////////////////////////////////////
/////////////////// GLOBAL ///////////////////
//////////////////////////////////////////////

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uvCoord;

    inline Vertex(glm::vec3 pos = glm::vec3(0,0,0), glm::vec3 col = glm::vec3(1,1,1), glm::vec2 uv = glm::vec2(0,0) ) : position(pos), color(col), uvCoord(uv)
    {

    }

};

//////////////////////////////////////////////



//////////////////////////////////////////////
/////////////////// CAMERA ///////////////////
//////////////////////////////////////////////

class Camera{
public:
    enum CameraType {ORTHOGRAPHIC, PERSPECTIVE};

private:
    glm::vec3 _position;
    glm::mat4 _projectionMat;
    glm::mat4 _viewMat;
    glm::mat4 _modelMat;

    CameraType _cameraType;

public:
    Camera(CameraType cameraType = CameraType::ORTHOGRAPHIC);

    const glm::mat4& getProjectionMat() const;
    const glm::mat4& getViewMat() const;
    const glm::mat4& getModelMat() const;

    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& pos);

};

Camera::Camera(CameraType cameraType) : _position(0,0,0), _cameraType(cameraType)
{
    if(cameraType == CameraType::ORTHOGRAPHIC)
        _projectionMat = glm::ortho( 0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, 0.001f, 100.f);
    else
        _projectionMat = glm::perspective(60.f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.001f, 1000.f);

    _viewMat = glm::lookAt(_position, _position + glm::vec3(0,0,-1), glm::vec3(0,1,0));

    setPosition(_position);
}

const glm::mat4& Camera::getProjectionMat() const
{
    return _projectionMat;
}

const glm::mat4& Camera::getViewMat() const
{
    return _viewMat;
}

const glm::mat4& Camera::getModelMat() const
{
    return _modelMat;
}

const glm::vec3& Camera::getPosition() const
{
    return _position;
}

void Camera::setPosition(const glm::vec3& pos)
{
    _position = pos;
    _viewMat = glm::lookAt(_position, _position + glm::vec3(0,0,-1),  glm::vec3(0,1,0) );
    _modelMat = glm::translate(glm::mat4(1), _position);
}

//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/////////////////// TRAIL RENDERER ///////////////////
//////////////////////////////////////////////////////

class TrailRenderer{
private:
    int _trailBuffer; //max number of point in _trailPoints
    std::vector<glm::vec3> _trailPoints;
    std::vector<Vertex> _trailVertex;
    std::vector<int> _trailIndex;
    GLuint _vao;
    GLuint _vbo;
    GLuint _ibo;
    float _trailWidth;
    int _frontIndex;
    int _backIndex;

public:
    TrailRenderer(float trailWidth = 1, int bufferSize = 16);
    ~TrailRenderer();

    void setTrailWidth(float trailWidth);

    void initGL();
    void pushBack(const glm::vec3& pointPosition, const glm::vec3 &color = glm::vec3(1,1,1));
    void popFront();
    void synchronizeVbos();
    void draw();
    void clearGL();
    void update();

    int getIndexCount();
};

TrailRenderer::TrailRenderer(float trailWidth, int bufferSize) : _trailBuffer(bufferSize) ,_vao(0), _vbo(0), _ibo(0), _trailWidth(trailWidth), _frontIndex(0), _backIndex(0)
{

}

TrailRenderer::~TrailRenderer()
{

}

void TrailRenderer::setTrailWidth(float trailWidth)
{
    _trailWidth = trailWidth;
}

void TrailRenderer::initGL()
{
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ibo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, (_trailBuffer - 1) * 4 * sizeof(Vertex) , nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (_trailBuffer - 1) * 6 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glEnableVertexAttribArray(0); //position
            glEnableVertexAttribArray(1); //color
            glEnableVertexAttribArray(2); //UV coords
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, color));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, uvCoord));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



}

void TrailRenderer::pushBack(const glm::vec3& pointPosition, const glm::vec3& color)
{
    int trailSize = _trailPoints.size();

    //activate this if you don't want to update trail if object isn't moving.
//    if(trailSize != 0 && glm::length2(_trailPoints[trailSize - 1] - pointPosition) < 0.000001f ) //static ?
//        return;

    if(trailSize == 0)
    {
        _trailPoints.push_back( pointPosition );
        return;
    }
    else //if( trailSize  < _trailBuffer )
    {
        if(trailSize == 1)
        {
             _trailPoints.push_back( pointPosition );
        }
        else
        {
            _trailPoints.push_back( _trailPoints[_backIndex] );
            _trailPoints.push_back( pointPosition );
        }

        trailSize = _trailPoints.size();

        glm::vec3 A = _trailPoints[trailSize - 2];
        glm::vec3 B = _trailPoints[trailSize - 1];
        glm::vec3 tangent = glm::normalize( B - A);
        glm::vec3 normalA(-tangent.y, tangent.x, 0);
        glm::vec3 normalB(-tangent.y, tangent.x, 0);


        //take the previous point into account to smooth the shape.
        if(trailSize >= 4)
        {
            glm::vec3 O =_trailPoints[_backIndex];
            glm::vec3 tangentO = glm::normalize( O - _trailPoints[_backIndex - 1]);
            glm::vec3 normalO(-tangentO.y, tangentO.x, 0);

            glm::vec3 smoothNormal = glm::normalize(normalB + normalO);
            normalA = smoothNormal;

            _trailVertex[_backIndex*2 - 1] = ( Vertex( A + normalA * _trailWidth*0.5f , color ) ); //b
            _trailVertex[_backIndex*2] = ( Vertex( A - normalA * _trailWidth*0.5f , color) ); //c
        }


       // +(a)------------------+(b)                            +
       // |   \                 |                               |
       // |       \      (1)    |                               | normal
       // A          \          B       ------tangent------->   |
       // |      (2)     \      |                               |
       // |                  \  |                               |
       // +(c)------------------+(d)

        int id_a = _trailVertex.size(); // id_b = id_a + 1, id_c = id_a + 2, ...

        _trailVertex.push_back( Vertex( A + normalA * _trailWidth*0.5f , color) ); //a
        _trailVertex.push_back( Vertex( B + normalB * _trailWidth*0.5f , color) ); //b

        _trailVertex.push_back( Vertex( B - normalB * _trailWidth*0.5f , color) ); //c
        _trailVertex.push_back( Vertex( A - normalA * _trailWidth*0.5f , color) ); //d


        //triangle (1) :
        _trailIndex.push_back( id_a );
        _trailIndex.push_back( id_a + 1 );
        _trailIndex.push_back( id_a + 2 );

        //triangle (2) :
        _trailIndex.push_back( id_a );
        _trailIndex.push_back( id_a + 2 );
        _trailIndex.push_back( id_a + 3 );

        _backIndex = _trailPoints.size() - 1;

        synchronizeVbos();
    }

}

void TrailRenderer::synchronizeVbos()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, (_trailBuffer - 1) * 4 * sizeof(Vertex) , nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _trailVertex.size() * sizeof(Vertex), &_trailVertex[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (_trailBuffer - 1) * 6 * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _trailIndex.size() * sizeof(uint32_t), &_trailIndex[0]);
}

void TrailRenderer::popFront()
{

    int frontIndex_points = _frontIndex;
    int frontIndex_vertices = _frontIndex*2;
    int frontIndex_indices = _frontIndex*3;


    // swap the 2 front trail point, with the 2 back trail point
    for(int i = 0; i < 2; i++){
        std::swap(_trailPoints[frontIndex_points +  1 - i], _trailPoints[_trailPoints.size() - 1]);
        _trailPoints.pop_back();
    }


    // swap the 4 front vertices, with the 6 back vertices
    for(int i = 0; i < 4; i++){
        std::swap(_trailVertex[frontIndex_vertices +  3 - i], _trailVertex[_trailVertex.size() - 1]);
        _trailVertex.pop_back();
    }

    // swap the 6 front indices, with the 6 back indices
    for(int i = 0; i < 6; i++){
        std::swap(_trailIndex[frontIndex_indices + 5 - i], _trailIndex[_trailIndex.size() - 1]);
        _trailIndex.pop_back();
    }

    //triangle (1) :
    _trailIndex[frontIndex_indices + 0] = ( frontIndex_vertices + 0 );
    _trailIndex[frontIndex_indices + 1] = ( frontIndex_vertices + 1 );
    _trailIndex[frontIndex_indices + 2] = ( frontIndex_vertices + 2 );

    //triangle (2) :
    _trailIndex[frontIndex_indices + 3] = ( frontIndex_vertices + 0 );
    _trailIndex[frontIndex_indices + 4] = ( frontIndex_vertices + 2 );
    _trailIndex[frontIndex_indices + 5] = ( frontIndex_vertices + 3 );

    synchronizeVbos();

    _frontIndex += 2;
    _backIndex = _frontIndex - 1;
    if(_frontIndex >= _trailPoints.size())
        _frontIndex = 0;

}

void TrailRenderer::draw()
{
    glBindVertexArray(_vao);
    int indexCount = getIndexCount();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TrailRenderer::clearGL()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void TrailRenderer::update()
{
    if(_trailPoints.size() > _trailBuffer)
    {
        popFront();
    }
}

int TrailRenderer::getIndexCount()
{
    return _trailIndex.size();
}

//////////////////////////////////////////



/////////////////////////////////////////////
/////////////////// TIMER ///////////////////
////////////////////////////////////////////

class Timer{
private:
    float _previousTime;
    SDLWindowManager* _windowManager;

public:
    Timer(SDLWindowManager* windowManager);
    float elapsedTime() const;
    void restart();
};

Timer::Timer(SDLWindowManager* windowManager) : _previousTime(0), _windowManager(windowManager)
{
    _previousTime = windowManager->getTime();
}

float Timer::elapsedTime() const
{
    return _windowManager->getTime() - _previousTime;
}

void Timer::restart()
{
    _previousTime = _windowManager->getTime();
}

/////////////////////////////////////////////




/////////////////////////////////////////////
/////////////////// MAIN ///////////////////
////////////////////////////////////////////

int main(int argc, char** argv) {

    // Initialize SDL and open a window :
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "TrailEngine");

    // Initialize glew for OpenGL3+ support :
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    //Initialisation :

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "/shaders/trail.vs.glsl",
                                  applicationPath.dirPath() + "/shaders/trail.fs.glsl");


    TrailRenderer trailRenderer(15, 128);
    trailRenderer.initGL();

    Timer timer(&windowManager);
    Timer FPSTimer(&windowManager);

    Camera camera(Camera::CameraType::ORTHOGRAPHIC);
    camera.setPosition(glm::vec3(0, 0, 10));

    glm::vec3 randomColor = glm::vec3(1,0,0);

    // Application loop :
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        //change random color
        if(timer.elapsedTime() >= 0.5f)
        {
            randomColor = glm::vec3( ((float) rand() / (RAND_MAX)), ((float) rand() / (RAND_MAX)), ((float) rand() / (RAND_MAX)));
            timer.restart();
        }
        //update trail
        trailRenderer.pushBack( glm::vec3( windowManager.getMousePosition().x, windowManager.getMousePosition().y, 0), randomColor );
        trailRenderer.update();

        //draw
        glClear(GL_COLOR_BUFFER_BIT);
            program.use();
                glUniformMatrix4fv( glGetUniformLocation(program.getGLId(), "ProjectionMatrix") , 1, false, glm::value_ptr(camera.getProjectionMat()));
                glUniformMatrix4fv( glGetUniformLocation(program.getGLId(), "ViewMatrix") , 1, false, glm::value_ptr(camera.getViewMat()));
            trailRenderer.draw();
        windowManager.swapBuffers();


        if(FPSTimer.elapsedTime() < 0.016f)
        {
            SDL_Delay((0.016f - FPSTimer.elapsedTime()) * 1000.f);
        }
        FPSTimer.restart();

    }

    return EXIT_SUCCESS;
}

////////////////////////////////////////////
