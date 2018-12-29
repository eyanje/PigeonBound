uniform sampler2D textureSampler;
in vec2 uv;

out vec4 color;

void main() {
    color = texture(textureSampler, uv);
}