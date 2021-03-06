# __BEGIN_LICENSE__
#  Copyright (c) 2006-2013, United States Government as represented by the
#  Administrator of the National Aeronautics and Space Administration. All
#  rights reserved.
#
#  The NASA Vision Workbench is licensed under the Apache License,
#  Version 2.0 (the "License"); you may not use this file except in
#  compliance with the License. You may obtain a copy of the License at
#  http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
# __END_LICENSE__


########################################################################
# sources
########################################################################

if MAKE_MODULE_BUNDLEADJUSTMENT

if MAKE_MODULE_INTERESTPOINT
if MAKE_MODULE_STEREO
# These deal with loading of interest points
relation_headers = CameraRelation.h ControlNetworkLoader.h

relation_sources = CameraRelation.cc ControlNetworkLoader.cc
endif
endif

include_HEADERS = BundleAdjustReport.h ControlNetwork.h ModelBase.h         \
                  AdjustBase.h AdjustRef.h AdjustRobustRef.h AdjustSparse.h \
                  AdjustRobustSparse.h $(relation_headers)

libvwBundleAdjustment_la_SOURCES = BundleAdjustReport.cc ControlNetwork.cc  \
                  $(relation_sources)

libvwBundleAdjustment_la_LIBADD = @MODULE_BUNDLEADJUSTMENT_LIBS@

lib_LTLIBRARIES = libvwBundleAdjustment.la

endif

########################################################################
# general
########################################################################

AM_CPPFLAGS = @VW_CPPFLAGS@
AM_LDFLAGS = @VW_LDFLAGS@ $(LIBTOOL_LIB_FLAGS)

SUBDIRS = . tests

includedir = $(prefix)/include/vw/BundleAdjustment

include $(top_srcdir)/config/rules.mak
