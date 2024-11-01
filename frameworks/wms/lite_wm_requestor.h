/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GRAPHIC_LITE_LITE_WM_REQUESTOR_H
#define GRAPHIC_LITE_LITE_WM_REQUESTOR_H

#include "gfx_utils/geometry2d.h"
#include "iproxy_client.h"
#include "iwindows_manager.h"
#include "lite_win_requestor.h"
#include "lite_wm_type.h"
#include "ipc_skeleton.h"

namespace OHOS {
class LiteWMRequestor : public IBufferConsumerListener {
public:
    static LiteWMRequestor* GetInstance();
    static int Callback(void* owner, int code, IpcIo* reply);
    static int32_t WmsMsgHandler(uint32_t code, IpcIo* data, IpcIo* reply, MessageOption option);
    static int32_t SurfaceRequestHandler(uint32_t code, IpcIo* data, IpcIo* reply, MessageOption option);

    void OnBufferAvailable() override;

    void ClientRegister();
    void GetLayerInfo();
    LiteWinRequestor* CreateWindow(const LiteWinConfig& config);
    void RemoveWindow(int32_t id);
    void GetEventData(DeviceData* data);

    void Screenshot();
    void SetScreenshotListener(IWindowsManager::ScreenshotListener* listener)
    {
        listener_ = listener;
    }

private:
    LiteWMRequestor();
    ~LiteWMRequestor() {}

    void ScreenShotClearup();
    IClientProxy* proxy_;
    IWindowsManager::ScreenshotListener* listener_;
    Surface* surface_;
    SvcIdentity sid_;
    IpcObjectStub objectStub_;
    LiteLayerInfo layerInfo_;
};
} // namespace OHOS
#endif
