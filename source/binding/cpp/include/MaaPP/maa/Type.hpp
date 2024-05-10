// IWYU pragma: private, include <MaaPP/MaaPP.hpp>

#pragma once

#include "MaaPP/module/Module.h"

#ifndef MAAPP_USE_MODULE

#include <string>

#include <MaaFramework/MaaAPI.h>
#include <meojson/json.hpp>

#include "MaaPP/maa/Image.hpp"
#include "MaaPP/maa/details/String.hpp"

#endif

namespace maa
{

MAAPP_EXPORT struct AnalyzeResult
{
    bool result = false;
    MaaRect rec_box = { 0, 0, 0, 0 };
    std::string rec_detail = "";
};

MAAPP_EXPORT struct RecognitionDetail
{
    bool hit = false;
    MaaRect hit_box = { 0, 0, 0, 0 };
    json::value detail;
    details::ImageList draws;

    bool query(MaaRecoId reco_id)
    {
        MaaBool hh;
        details::String dd;
        auto res = MaaQueryRecognitionDetail(reco_id, &hh, &hit_box, dd.handle(), draws.handle());
        if (res) {
            hit = !!hh;
            detail = json::parse(dd.str()).value_or(json::object {});
            return true;
        }
        else {
            return false;
        }
    }
};

MAAPP_EXPORT struct RunningDetail
{
    MaaRecoId reco_id = MaaInvalidId;
    bool success = false;

    bool query(MaaRunningId running_id)
    {
        MaaBool ss;
        auto res = MaaQueryRunningDetail(running_id, &reco_id, &ss);
        if (res) {
            success = !!ss;
            return true;
        }
        else {
            return false;
        }
    }
};

}
