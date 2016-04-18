#include <stdafx.h>
#include <tinyxml.h>
#include <vector>
#include "params.h"

#define PATH_FILENAME "path.xml"

bool ReadParams(const char* filename, Params& params) {
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()) {
		fprintf(stderr, "Couldn't read params from %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem) {
		fprintf(stderr, "Invalid format for %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);
	TiXmlHandle hParams = hRoot.FirstChildElement("params");

	//TiXmlElement* paramElem = hParams.FirstChild().Element();
	//for (paramElem; paramElem; paramElem = paramElem->NextSiblingElement())
	//{
	//    const char* paramName = paramElem->Value();
	//    if (!strcmp(paramName, "max_velocity"))
	//    {
	//        const char* elemText = paramElem->GetText();
	//        params.max_velocity = static_cast<float>(atof(elemText));
	//    }
	//}

	TiXmlElement* paramElem = hParams.FirstChildElement("max_velocity").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_velocity);

	paramElem = hParams.FirstChildElement("max_acceleration").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_acceleration);

	paramElem = hParams.FirstChildElement("dest_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.dest_radius);

	paramElem = hParams.FirstChildElement("arrive_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.arrive_radius);

	paramElem = hParams.FirstChildElement("targetPosition").Element();
	if (paramElem) {
		paramElem->Attribute("x", &params.target_position.mX);
		paramElem->Attribute("y", &params.target_position.mY);
	}

	paramElem = hParams.FirstChildElement("max_angular_velocity").Element();
	if (paramElem) {
		paramElem->Attribute("value", &params.max_angular_velocity);
	}

	paramElem = hParams.FirstChildElement("max_angular_acceleration").Element();
	if (paramElem) {
		paramElem->Attribute("value", &params.max_angular_acceleration);
	}

	paramElem = hParams.FirstChildElement("angular_dest_radius").Element();
	if (paramElem) {
		paramElem->Attribute("value", &params.angular_dest_radius);
	}

	paramElem = hParams.FirstChildElement("angular_arrive_radius").Element();
	if (paramElem) {
		paramElem->Attribute("value", &params.angular_arrive_radius);
	}

	paramElem = hParams.FirstChildElement("targetRotation").Element();
	if (paramElem) {
		paramElem->Attribute("value", &params.target_rotation);
	}

	//parse file and fill points[]
	TiXmlDocument docPath(PATH_FILENAME);
	if (!docPath.LoadFile()) {
		fprintf(stderr, "Couldn't read params from %s", PATH_FILENAME);
		return false;
	}

	TiXmlHandle pDoc(&docPath);

	TiXmlElement* pathElem;
	pathElem = pDoc.FirstChildElement().Element();
	if (!pathElem) {
		fprintf(stderr, "Invalid format for %s", PATH_FILENAME);
		return false;
	}

	TiXmlHandle pRoot(pathElem);
	TiXmlHandle pPoints = pRoot.FirstChildElement("points");
	Point p;

	uint16_t numPoints = 0;
	bool end = false;
	while (!end) {
		TiXmlElement* point = pPoints.Child("point", numPoints++).Element();
		if (point) {
			point->Attribute("x", &p.x);
			point->Attribute("y", &p.y);
			params.points.push_back(p);
		} else {
			end = true;
		}
	}

	return true;
}