// __BEGIN_LICENSE__
//  Copyright (c) 2006-2013, United States Government as represented by the
//  Administrator of the National Aeronautics and Space Administration. All
//  rights reserved.
//
//  The NASA Vision Workbench is licensed under the Apache License,
//  Version 2.0 (the "License"); you may not use this file except in
//  compliance with the License. You may obtain a copy of the License at
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// __END_LICENSE__


#ifndef __VW_CARTOGRAPHY_DATUM_H__
#define __VW_CARTOGRAPHY_DATUM_H__

#include <string>
#include <ostream>
#include <cmath>

#include <vw/Math/Vector.h>
#include <vw/Math/Matrix.h>

#if defined(VW_HAVE_PKG_PROTOBUF) && VW_HAVE_PKG_PROTOBUF==1
#include <vw/Cartography/DatumDesc.pb.h>
#endif

// For an excellent discussion of the various concepts, terms, and
// issues involved in global coordinate systems, see:
// http://www.posc.org/Epicentre.2_2/DataModel/ExamplesofUsage/eu_cs.html

namespace vw {
namespace cartography {

  /// A geodetic datum, i.e. a reference ellipsoid coordinate system
  /// for a planetary body.  This implementation assumes a relatively
  /// modern notion of a datum, ie. a geocentric bi-axial ellipsoidal
  /// model.
  ///
  /// To express a spherical datum, set the semi-major axis equal to
  /// the semi-minor axis.  All angles are measured in degrees, and
  /// all distances are measured in meters.  This class incorporates a
  /// prime meridian offset, which is not usually strictly considered
  /// part of the datum but which has no better place to be right now.
  class Datum {
    std::string m_name;
    std::string m_spheroid_name;
    std::string m_meridian_name;
    double m_semi_major_axis;
    double m_semi_minor_axis;
    double m_meridian_offset;
    bool m_geocentric;
    std::string m_proj_str;

  public:
    /// The default constructor creates a WGS84 datum.
    Datum() {
      set_well_known_datum("WGS84");
    }

    /// Constructs a well-known datum by name.
    Datum( std::string const& name ) {
      set_well_known_datum( name );
    }

    /// This constructor allows the user to create a custom datum.
    Datum(std::string const& name,
          std::string const& spheroid_name,
          std::string const& meridian_name,
          double semi_major_axis,
          double semi_minor_axis,
          double meridian_offset);

#if defined(VW_HAVE_PKG_PROTOBUF) && VW_HAVE_PKG_PROTOBUF==1
    /// Build a constructor from a DatumDesc
    Datum(DatumDesc const& desc) :
        m_name(desc.name()),
        m_spheroid_name(desc.spheroid_name()),
        m_meridian_name(desc.meridian_name()),
        m_semi_major_axis(desc.semi_major_axis()),
        m_semi_minor_axis(desc.semi_minor_axis()),
        m_meridian_offset(desc.meridian_offset()),
        m_geocentric(desc.geocentric()),
        m_proj_str(desc.proj_str()) {}

    /// Create a DatumDesc from the datum
    DatumDesc build_desc() const;
#endif

    /// Options include: WGS84, WGS72, NAD27, or NAD83.
    void set_well_known_datum(std::string const& name);

    std::string &name() { return m_name; }
    std::string const& name() const { return m_name; }

    std::string &spheroid_name() { return m_spheroid_name; }
    std::string const& spheroid_name() const { return m_spheroid_name; }

    std::string &meridian_name() { return m_meridian_name; }
    std::string const& meridian_name() const { return m_meridian_name; }

    void set_semi_major_axis(double val);
    double semi_major_axis() const { return m_semi_major_axis; }

    void set_semi_minor_axis(double val);
    double semi_minor_axis() const { return m_semi_minor_axis; }

    double &meridian_offset() { return m_meridian_offset; }
    double meridian_offset() const { return m_meridian_offset; }

    void set_geocentric(bool val);
    bool geocentric() const { return m_geocentric; }

    std::string &proj4_str() { return m_proj_str; }
    std::string const& proj4_str() const { return m_proj_str; }

    double radius(double lon, double lat) const;

    /// return geocentric latitude corresponding to geodetic lat:
    double geocentric_latitude(double lat) const;

    /// return radius of curvature in the prime vertical.
    double radius_of_curvature(double lon, double lat) const;

    /// return distance from the center of the Earth (lat,lon are geodetic,
    //// alt is ellipsoidal or geodetic height).
    double geocentric_radius(double lon, double lat, double alt = 0.0) const;

    double inverse_flattening() const;

    /// Return cartesian (ECEF) coordinates of geodetic coordinates p [Lon, Lat, Height]
    Vector3 geodetic_to_cartesian( Vector3 const& llh ) const;

    // Return rotation matrix for converting between ECEF and NED
    // vectors. If v is a Cartesian (ECEF) vector, this matrix times v
    // will find v's components in the North, East, and Down
    // directions at given lon and lat.
    Matrix3x3 lonlat_to_ned_matrix(Vector2 const& lonlat) const;

    Vector3 cartesian_to_geodetic( Vector3 const& xyz ) const;
  };

  std::ostream& operator<<(std::ostream& os, const Datum& datum);


}} // namespace vw::cartography

#endif // __VW_CARTOGRAPHY_DATUM_H__

