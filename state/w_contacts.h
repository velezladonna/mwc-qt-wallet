// Copyright 2019 The MWC Developers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CONTACTS_H
#define CONTACTS_H


#include "state.h"
#include "../wallet/wallet.h"
#include "../core/appcontext.h"

namespace state {


class Contacts : public State
{
public:
    Contacts(StateContext * context);
    virtual ~Contacts() override;

    // Get the contacts
    QVector<core::ContactRecord> getContacts();

    QPair<bool, QString> addContact( const core::ContactRecord & contact );
    QPair<bool, QString> deleteContact( const core::ContactRecord & contact );
    QPair<bool, QString> updateContact( const core::ContactRecord & prevValue, const core::ContactRecord & newValue );

    QVector<int> getColumnsWidhts() const;
    void updateColumnsWidhts(const QVector<int> & width);

protected:
    virtual NextStateRespond execute() override;
    virtual QString getHelpDocName() override {return "contacts.html";}

};

}

#endif // CONTACTS_H
