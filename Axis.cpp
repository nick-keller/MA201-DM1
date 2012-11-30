#include "Axis.h"

Axis::Axis(RenderWindow& app, MouseWrapper& mouse) : m_app(app), m_mouse(mouse)
{
    // Init view
    m_view = View(Vector2f(0,0), Vector2f(10,2));
    this->updateView();
}

void Axis::reset()
{
    m_view = View(Vector2f(0,0), Vector2f(10,2));
    this->updateView();
}

void Axis::render() const
{
    const FloatRect& boundaries = this->getBoundaries();
    const Vector2f zoom = this->getZoom();

    // Enable OpenGL
    m_app.SetActive();
    m_app.Draw(Shape());

    glBegin(GL_LINES);
        // Draw cursor position
        glColor3ub(200,200,200);
        glVertex2d(this->getCursorPos().x, boundaries.Bottom);
        glVertex2d(this->getCursorPos().x, boundaries.Top);

        // Draw axis
        glColor3ub(0,0,0);
        glVertex2d(boundaries.Left, 0);
        glVertex2d(boundaries.Right, 0);
        glVertex2d(0, boundaries.Bottom);
        glVertex2d(0, boundaries.Top);

        // Draw X ruller
        for(int i((int)boundaries.Left); i<boundaries.Right; ++i)
        {
            if(i%10 == 0 && zoom.x>3){
                glVertex2d(i, 0);
                glVertex2d(i, 20.f/zoom.y);
            }
            else if(i%5 == 0 && zoom.x>5) {
                glVertex2d(i, 0);
                glVertex2d(i, 10.f/zoom.y);
            }
            else if(zoom.x>10) {
                glVertex2d(i, 0);
                glVertex2d(i, 5.f/zoom.y);
            }
        }

        // Draw Y ruller
        for(int i((int)boundaries.Top); i<boundaries.Bottom; ++i)
        {
            if(i%10 == 0 && zoom.y>3){
                glVertex2d(0, i);
                glVertex2d(-20.f/zoom.x, i);
            }
            else if(i%5 == 0 && zoom.y>5) {
                glVertex2d(0, i);
                glVertex2d(-10.f/zoom.x, i);
            }
            else if(zoom.y>10) {
                glVertex2d(0, i);
                glVertex2d(-5.f/zoom.x, i);
            }
        }
    glEnd();

    // Draw arrows
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,0);

        glVertex2d(boundaries.Right, 0);
        glVertex2d(boundaries.Right-10.f/zoom.x, -6.f/zoom.y);
        glVertex2d(boundaries.Right-10.f/zoom.x,  6.f/zoom.y);

        glVertex2d(0, boundaries.Top);
        glVertex2d(-6.f/zoom.x, boundaries.Top+10.f/zoom.y);
        glVertex2d( 6.f/zoom.x, boundaries.Top+10.f/zoom.y);
    glEnd();

}

void Axis::update()
{
    if(m_mouse.isBtnDown(MouseWrapper::Left))
        this->move(m_mouse.getMovement());

    else if(m_mouse.isBtnDown(MouseWrapper::Right))
        this->zoom(m_mouse.getMovement());
}

const FloatRect& Axis::getBoundaries() const
{
    return m_view.GetRect();
}

const Vector2f Axis::getZoom() const
{
    const FloatRect& boundaries = this->getBoundaries();
    Vector2f zoom;

    // Calculate zoom according to window size and view boundaries
    zoom.x = (float)m_app.GetWidth()/(boundaries.Right-boundaries.Left);
    zoom.y = (float)m_app.GetHeight()/(boundaries.Bottom-boundaries.Top);

    return zoom;
}

void Axis::updateView()
{
    m_app.SetView(m_view);
}

void Axis::move(Vector2f dir)
{
    const Vector2f zoom = this->getZoom();

    // Scale dir according to zoom
    dir.x /= -zoom.x;
    dir.y /= -zoom.y;
    m_view.Move(dir);

    this->updateView();
}

void Axis::zoom(Vector2f dir)
{
    const Vector2f zoom = this->getZoom();
    Vector2f halfSize = m_view.GetHalfSize();

    // Scale half-size according to zoom
    halfSize.x += -dir.x/zoom.x;
    halfSize.y += dir.y/zoom.y;
    m_view.SetHalfSize(halfSize);

    this->updateView();
}

const Vector2f Axis::getCursorPos() const
{
    const FloatRect& boundaries = this->getBoundaries();

    // Convert pixels to graph unit
    return Vector2f(boundaries.Left+(boundaries.Right-boundaries.Left)*m_mouse.getX()/m_app.GetWidth(),0);
}
