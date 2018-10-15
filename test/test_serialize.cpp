#include <catch/catch.hpp>

#include <geoshape/Point2D.h>
#include <geoshape/Rect.h>
#include <geoshape/Circle.h>
#include <geoshape/Bezier.h>
#include <geoshape/Polyline.h>
#include <geoshape/Polygon.h>
#include <geoshape/Serialize.h>

#include <js/RTTR.h>

namespace gs
{

TEST_CASE("rttr")
{
	SECTION("point2d")
	{
		Point2D pt(sm::vec2(1, 2));

		auto prop = rttr::type::get(pt).get_property("pos");
		prop.set_value(pt, sm::vec2(3, 4));

		REQUIRE(pt.GetPos() == sm::vec2(3, 4));

		auto var = prop.get_value(pt);
		REQUIRE(var.is_valid());
		REQUIRE(var.can_convert<sm::vec2>());
		bool ok = false;
		auto pos = var.convert<sm::vec2>(&ok);
		REQUIRE(ok);
		REQUIRE(pos == sm::vec2(3, 4));
	}

	SECTION("rect")
	{
		Rect r(sm::rect(100, 200));

		auto prop = rttr::type::get(r).get_property("rect");
		prop.set_value(r, sm::rect(300, 400));

		REQUIRE(r.GetRect() == sm::rect(300, 400));

		auto var = prop.get_value(r);
		REQUIRE(var.is_valid());
		REQUIRE(var.can_convert<sm::rect>());
		bool ok = false;
		auto rect = var.convert<sm::rect>(&ok);
		REQUIRE(ok);
		REQUIRE(rect == sm::rect(300, 400));
	}

	SECTION("circle")
	{
		Circle c(sm::vec2(1, 2), 3);

		auto prop_c = rttr::type::get(c).get_property("center");
		prop_c.set_value(c, sm::vec2(4, 5));
		auto prop_r = rttr::type::get(c).get_property("radius");
		prop_r.set_value(c, 6.0f);

		REQUIRE(c.GetCenter() == sm::vec2(4, 5));
		REQUIRE(c.GetRadius() == 6.0f);

		auto var_c = prop_c.get_value(c);
		REQUIRE(var_c.is_valid());
		REQUIRE(var_c.can_convert<sm::vec2>());
		bool ok = false;
		auto center = var_c.convert<sm::vec2>(&ok);
		REQUIRE(ok);
		REQUIRE(center == sm::vec2(4, 5));

		auto var_r = prop_r.get_value(c);
		REQUIRE(var_r.is_valid());
		REQUIRE(var_r.can_convert<float>());
		ok = false;
		auto radius = var_r.convert<float>(&ok);
		REQUIRE(ok);
		REQUIRE(radius == 6);
	}

	SECTION("bezier")
	{
		Bezier bz({ sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) });

		auto prop = rttr::type::get(bz).get_property("ctrl_pos");

		const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT> ctrl_nodes = {
			sm::vec2(11, 12), sm::vec2(13, 14), sm::vec2(15, 16), sm::vec2(17, 18)
		};
		prop.set_value(bz, ctrl_nodes);

		REQUIRE(bz.GetCtrlPos()[0] == sm::vec2(11, 12));
		REQUIRE(bz.GetCtrlPos()[1] == sm::vec2(13, 14));
		REQUIRE(bz.GetCtrlPos()[2] == sm::vec2(15, 16));
		REQUIRE(bz.GetCtrlPos()[3] == sm::vec2(17, 18));

		auto var = prop.get_value(bz);
		REQUIRE(var.is_valid());
		REQUIRE(var.can_convert<const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>&>());
		bool ok = false;
		auto cps = var.convert<std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>>(&ok);
		REQUIRE(ok);
		REQUIRE(cps[0] == sm::vec2(11, 12));
		REQUIRE(cps[1] == sm::vec2(13, 14));
		REQUIRE(cps[2] == sm::vec2(15, 16));
		REQUIRE(cps[3] == sm::vec2(17, 18));
	}

	SECTION("polyline")
	{
		Polyline p({ sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) });

		auto prop = rttr::type::get(p).get_property("vertices");

		const std::vector<sm::vec2> vs = {
			sm::vec2(11, 12), sm::vec2(13, 14), sm::vec2(15, 16), sm::vec2(17, 18)
		};
		prop.set_value(p, vs);

		REQUIRE(p.GetVertices()[0] == sm::vec2(11, 12));
		REQUIRE(p.GetVertices()[1] == sm::vec2(13, 14));
		REQUIRE(p.GetVertices()[2] == sm::vec2(15, 16));
		REQUIRE(p.GetVertices()[3] == sm::vec2(17, 18));

		auto var = prop.get_value(p);
		REQUIRE(var.is_valid());
		REQUIRE(var.can_convert<const std::vector<sm::vec2>&>());
		bool ok = false;
		auto vs2 = var.convert<std::vector<sm::vec2>>(&ok);
		REQUIRE(ok);
		REQUIRE(vs2[0] == sm::vec2(11, 12));
		REQUIRE(vs2[1] == sm::vec2(13, 14));
		REQUIRE(vs2[2] == sm::vec2(15, 16));
		REQUIRE(vs2[3] == sm::vec2(17, 18));
	}

	SECTION("polygon")
	{
		Polygon p({ sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) });

		auto prop = rttr::type::get(p).get_property("vertices");

		const std::vector<sm::vec2> vs = {
			sm::vec2(11, 12), sm::vec2(13, 14), sm::vec2(15, 16), sm::vec2(17, 18)
		};
		prop.set_value(p, vs);

		REQUIRE(p.GetVertices()[0] == sm::vec2(11, 12));
		REQUIRE(p.GetVertices()[1] == sm::vec2(13, 14));
		REQUIRE(p.GetVertices()[2] == sm::vec2(15, 16));
		REQUIRE(p.GetVertices()[3] == sm::vec2(17, 18));

		auto var = prop.get_value(p);
		REQUIRE(var.is_valid());
		REQUIRE(var.can_convert<const std::vector<sm::vec2>&>());
		bool ok = false;
		auto vs2 = var.convert<std::vector<sm::vec2>>(&ok);
		REQUIRE(ok);
		REQUIRE(vs2[0] == sm::vec2(11, 12));
		REQUIRE(vs2[1] == sm::vec2(13, 14));
		REQUIRE(vs2[2] == sm::vec2(15, 16));
		REQUIRE(vs2[3] == sm::vec2(17, 18));
	}
}

TEST_CASE("json")
{
	Serialize::Init();

	SECTION("point2d")
	{
		std::shared_ptr<Shape> shape = std::make_shared<Point2D>(sm::vec2(1, 2));

		auto json = js::RTTR::ToRapidJson(shape);
//		printf("%s\n", json.c_str());
		Point2D p;
		js::RTTR::FromRapidJson(json, p);

		REQUIRE(p.GetPos().x == 1);
		REQUIRE(p.GetPos().y == 2);
	}

	SECTION("rect")
	{
		std::shared_ptr<Shape> shape = std::make_shared<Rect>(sm::rect(100, 200));

		auto json = js::RTTR::ToRapidJson(shape);
//		printf("%s\n", json.c_str());
		Rect r;
		js::RTTR::FromRapidJson(json, r);

		REQUIRE(r.GetRect() == sm::rect(100, 200));
	}

	SECTION("circle")
	{
		std::shared_ptr<Shape> shape = std::make_shared<Circle>(sm::vec2(1, 2), 3);

		auto json = js::RTTR::ToRapidJson(shape);
//		printf("%s\n", json.c_str());
		Circle c;
		js::RTTR::FromRapidJson(json, c);

		REQUIRE(c.GetCenter() == sm::vec2(1, 2));
		REQUIRE(c.GetRadius() == 3);
	}

	SECTION("bezier")
	{
		std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT> cnodes = {
			sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8)
		};
		std::shared_ptr<Shape> shape = std::make_shared<Bezier>(cnodes);

		auto json = js::RTTR::ToRapidJson(shape);
//		printf("%s\n", json.c_str());
		Bezier bz;
		js::RTTR::FromRapidJson(json, bz);

		auto& cp = bz.GetCtrlPos();
		REQUIRE(cp[0] == sm::vec2(1, 2));
		REQUIRE(cp[1] == sm::vec2(3, 4));
		REQUIRE(cp[2] == sm::vec2(5, 6));
		REQUIRE(cp[3] == sm::vec2(7, 8));
	}

	SECTION("polyline")
	{
		std::vector<sm::vec2> cnodes = {
			sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8)
		};
		std::shared_ptr<Shape> shape = std::make_shared<Polyline>(cnodes);

		auto json = js::RTTR::ToRapidJson(shape);
//		printf("%s\n", json.c_str());
		Polyline pline;
		js::RTTR::FromRapidJson(json, pline);

		auto& vs = pline.GetVertices();
		REQUIRE(vs[0] == sm::vec2(1, 2));
		REQUIRE(vs[1] == sm::vec2(3, 4));
		REQUIRE(vs[2] == sm::vec2(5, 6));
		REQUIRE(vs[3] == sm::vec2(7, 8));
	}

	SECTION("polygon")
	{
		std::vector<sm::vec2> cnodes = {
			sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8)
		};
		std::shared_ptr<Shape> shape = std::make_shared<Polygon>(cnodes);

		auto json = js::RTTR::ToRapidJson(shape);
//		printf("%s\n", json.c_str());
		Polygon pline;
		js::RTTR::FromRapidJson(json, pline);

		auto& vs = pline.GetVertices();
		REQUIRE(vs[0] == sm::vec2(1, 2));
		REQUIRE(vs[1] == sm::vec2(3, 4));
		REQUIRE(vs[2] == sm::vec2(5, 6));
		REQUIRE(vs[3] == sm::vec2(7, 8));
	}
}

}