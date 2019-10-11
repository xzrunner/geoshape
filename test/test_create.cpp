#include <catch/catch.hpp>

#include <geoshape/Point2D.h>
#include <geoshape/Rect.h>
#include <geoshape/Circle.h>
#include <geoshape/Bezier.h>
#include <geoshape/Polyline2D.h>
#include <geoshape/Polygon2D.h>

namespace gs
{

TEST_CASE("stack")
{
	SECTION("point2d")
	{
		Point2D pt(sm::vec2(1, 2));
		REQUIRE(pt.GetPos() == sm::vec2(1, 2));
	}

	SECTION("rect")
	{
		Rect r(sm::rect(100, 200));
		REQUIRE(r.GetRect() == sm::rect(100, 200));
	}

	SECTION("circle")
	{
		Circle c(sm::vec2(1, 2), 3);
		REQUIRE(c.GetCenter() == sm::vec2(1, 2));
		REQUIRE(c.GetRadius() == 3);
	}

	SECTION("bezier")
	{
		Bezier bz({ sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) });
		auto cp = bz.GetCtrlPos();
		REQUIRE(cp[0] == sm::vec2(1, 2));
		REQUIRE(cp[1] == sm::vec2(3, 4));
		REQUIRE(cp[2] == sm::vec2(5, 6));
		REQUIRE(cp[3] == sm::vec2(7, 8));
	}

	SECTION("polyline")
	{
		Polyline2D pline({ sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) });
		auto& vs = pline.GetVertices();
		REQUIRE(vs[0] == sm::vec2(1, 2));
		REQUIRE(vs[1] == sm::vec2(3, 4));
		REQUIRE(vs[2] == sm::vec2(5, 6));
		REQUIRE(vs[3] == sm::vec2(7, 8));
	}

	SECTION("polygon")
	{
		Polygon2D pgon({ sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) });
		auto& vs = pgon.GetVertices();
		REQUIRE(vs[0] == sm::vec2(1, 2));
		REQUIRE(vs[1] == sm::vec2(3, 4));
		REQUIRE(vs[2] == sm::vec2(5, 6));
		REQUIRE(vs[3] == sm::vec2(7, 8));
	}
}

TEST_CASE("heap_rttr")
{
	SECTION("point2d")
	{
		auto type = rttr::type::get_by_name("gs_point2d");
		REQUIRE(type.is_valid());
		auto obj = type.create({ sm::vec2(1, 2) });
		REQUIRE(obj.is_valid());
		REQUIRE(obj.is_type<std::shared_ptr<gs::Point2D>>());
		auto pt = obj.get_value<std::shared_ptr<gs::Point2D>>();
		REQUIRE(pt->GetPos() == sm::vec2(1, 2));
	}

	SECTION("rect")
	{
		auto type = rttr::type::get_by_name("gs_rect");
		REQUIRE(type.is_valid());
		auto obj = type.create({ sm::rect(100, 200) });
		REQUIRE(obj.is_valid());
		REQUIRE(obj.is_type<std::shared_ptr<gs::Rect>>());
		auto rect = obj.get_value<std::shared_ptr<gs::Rect>>();
		REQUIRE(rect->GetRect() == sm::rect(100, 200));
	}

	SECTION("circle")
	{
		auto type = rttr::type::get_by_name("gs_circle");
		auto ctor = type.get_constructor({ rttr::type::get<sm::vec2>(), rttr::type::get<float>() });
		auto obj = ctor.invoke(sm::vec2(1, 2), 3.0f);
		REQUIRE(obj.is_valid());
		REQUIRE(obj.is_type<std::shared_ptr<gs::Circle>>());
		auto circle = obj.get_value<std::shared_ptr<gs::Circle>>();
		REQUIRE(circle->GetCenter() == sm::vec2(1, 2));
		REQUIRE(circle->GetRadius() == 3);
	}

	SECTION("bezier")
	{
		auto type = rttr::type::get_by_name("gs_bezier");
		REQUIRE(type.is_valid());

		std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT> ctrl_nodes = {
			sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8)
		};
		auto obj = type.create({ ctrl_nodes });
		REQUIRE(obj.is_valid());
		REQUIRE(obj.is_type<std::shared_ptr<gs::Bezier>>());
		auto bz = obj.get_value<std::shared_ptr<gs::Bezier>>();
		auto cp = bz->GetCtrlPos();
		REQUIRE(cp[0] == sm::vec2(1, 2));
		REQUIRE(cp[1] == sm::vec2(3, 4));
		REQUIRE(cp[2] == sm::vec2(5, 6));
		REQUIRE(cp[3] == sm::vec2(7, 8));
	}

	SECTION("polyline")
	{
		auto type = rttr::type::get_by_name("gs_polyline");
		REQUIRE(type.is_valid());
		std::vector<sm::vec2> points = { sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) };
		auto obj = type.create({ points });
		REQUIRE(obj.is_valid());
		REQUIRE(obj.is_type<std::shared_ptr<gs::Polyline2D>>());
		auto pline = obj.get_value<std::shared_ptr<gs::Polyline2D>>();
		auto vs = pline->GetVertices();
		REQUIRE(vs[0] == sm::vec2(1, 2));
		REQUIRE(vs[1] == sm::vec2(3, 4));
		REQUIRE(vs[2] == sm::vec2(5, 6));
		REQUIRE(vs[3] == sm::vec2(7, 8));
	}

	SECTION("polygon")
	{
		auto type = rttr::type::get_by_name("gs_polygon");
		REQUIRE(type.is_valid());
		std::vector<sm::vec2> points = { sm::vec2(1, 2), sm::vec2(3, 4), sm::vec2(5, 6), sm::vec2(7, 8) };
		auto obj = type.create({ points });
		REQUIRE(obj.is_valid());
		REQUIRE(obj.is_type<std::shared_ptr<gs::Polygon2D>>());
		auto pline = obj.get_value<std::shared_ptr<gs::Polygon2D>>();
		auto vs = pline->GetVertices();
		REQUIRE(vs[0] == sm::vec2(1, 2));
		REQUIRE(vs[1] == sm::vec2(3, 4));
		REQUIRE(vs[2] == sm::vec2(5, 6));
		REQUIRE(vs[3] == sm::vec2(7, 8));
	}
}

//TEST_CASE("clone")
//{
//	std::shared_ptr<Shape> shape = std::make_shared<Rect>(sm::rect(100, 200));
//
//	auto& ctor0 = shape->get_type().get_constructor({ rttr::type::get<const gs::Rect&>() });
//	REQUIRE(ctor0.is_valid());
//
//	auto& ctor1 = shape->get_type().get_constructor({ shape->get_type() });
//	REQUIRE(ctor1.is_valid());
//
//	//gs::Rect rr;
//	auto obj = ctor1.invoke(*shape);
////	shape->get_type().get_raw_type();
////	auto obj = ctor1.invoke(*std::dynamic_pointer_cast<shape->get_type().get_raw_type()>(shape));
////	auto obj = ctor1.invoke(rttr::rttr_cast<shape->get_type()>(*shape));
////	CHECK(obj.is_valid());
//
//	if (obj.get_type().is_pointer())
//	{
//		auto dtor = shape->get_type().get_destructor();
//		dtor.invoke(obj);
//	}
//}

}