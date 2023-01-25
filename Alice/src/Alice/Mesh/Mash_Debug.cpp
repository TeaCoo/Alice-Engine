#include "pch.h"
#include "Mash_Debug.h"
#include "Alice/Buffer/MeshBuffer.h"
#include "Alice/FileIO/ShaderProcessor.h"
#include "Alice/Texture/Texture.h"
#include "Alice/FileIO/ObjFileReader.h"

Alice::Mash_Debug::Mash_Debug()
{
	this->mesh_gui_ptr = new Mesh_Debug_GUI();

	ObjFileReader obj("../asset/model/sphere.obj");
	MeshBuffer meshBuffer(obj.meshes, BatchType::TEXTURE);

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	glBufferData(GL_ARRAY_BUFFER,
		meshBuffer.length_per_vertex * meshBuffer.vertexCount * sizeof(float),
		meshBuffer.vertex_buffer->positions,
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, meshBuffer.length_per_vertex * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, meshBuffer.length_per_vertex * sizeof(float), (const void *)(3 * sizeof(float)));

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	index_count = meshBuffer.indexCount;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		meshBuffer.indexCount * sizeof(unsigned int),
		meshBuffer.index_buffer->index,
		GL_STATIC_DRAW);

	ShaderProcessor shaderReader("../asset/shader/default.vert", "../asset/shader/default.frag");
	unsigned int shader = CreateShader(shaderReader.vert, shaderReader.frag);
	glUseProgram(shader);
	
	unsigned int m_RendererID;
	
	Texture *texture = new Texture("../asset/icon/logo/texture.png");
	texture->Bind();

	int location = glGetUniformLocation(shader, "u_Texture");
	glUniform1i(location, 0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Alice::Mash_Debug::OnUpdate()
{
	if (this->drawline)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}

Alice::Mash_Debug::~Mash_Debug()
{
	glDeleteBuffers(1, &id);
	glDeleteBuffers(1, &index);
	delete this->mesh_gui_ptr;
}

void Alice::Mash_Debug::OnImGuiRender()
{
	static bool show = true;
	//ImGui::ShowDemoWindow(&show);
	this->mesh_gui_ptr->ShowGUI(&show);
	// connect GUI with data in this class
	this->drawline = this->mesh_gui_ptr->drawline;
}
