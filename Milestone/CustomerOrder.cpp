// Name: Lean Junio
// Seneca Student ID: 019-109-123
// Seneca email: ljjunio@myseneca.ca
// Date of completion: November 17, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

// CustomerOrder.cpp

#include <iomanip>
#include <iostream>
#include "Utilities.h"
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder()
    : m_name(""),
      m_product(""),
      m_cntItem(0),
      m_lstItem(nullptr)
{
}

CustomerOrder::CustomerOrder(const std::string &record)
    : CustomerOrder()
{
    Utilities localUtility;
    bool more = true;
    size_t next_pos = 0u, beg = 0u;

    m_name = localUtility.extractToken(record, next_pos, more);
    m_product = localUtility.extractToken(record, next_pos, more);

    if (localUtility.getFieldWidth() > m_widthField)
        m_widthField = localUtility.getFieldWidth();

    beg = next_pos;
    m_cntItem = 0u;
    
    // Count how many products exists
    while (more)
    {
        localUtility.extractToken(record, next_pos, more);
        m_cntItem++;
    }

    // Allocate memory
    m_lstItem = new ItemInfo*[m_cntItem];
    more = true;

    // Take the addresses of the extracted tokens and add them into m_lstItem
    localUtility.setFieldWidth(0);
    for (int i = 0; i < static_cast<int>(m_cntItem); i++)
        m_lstItem[i] = new ItemInfo(localUtility.extractToken(record, beg, more));

}

CustomerOrder::CustomerOrder(const CustomerOrder& other)
{
    throw std::string("Invalid Operation: CustomerOrder objects cannot be copied.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
{
    *this = std::move(other);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other)
{
    if (this != &other)
    {
        m_name = other.m_name;
        m_product = other.m_product;
        m_cntItem = other.m_cntItem;
        m_lstItem = other.m_lstItem;

        other.m_lstItem = nullptr;
    }

    return *this;
}

CustomerOrder::~CustomerOrder()
{
    delete [] m_lstItem;
}

// Takes the fill state of the item specified, skip if the item is not found and return true
bool CustomerOrder::getItemFillState(std::string item) const
{
    bool filled = true;

    for (int i = 0; i < static_cast<int>(m_cntItem); i++)
        if (m_lstItem[i]->m_itemName == item)
            if (!m_lstItem[i]->m_fillState)
            {
                filled = false;
                break;
            }
    
    return filled;
}

bool CustomerOrder::getOrderFillState() const
    // If any of the items have not yet been filled, return false
{
    for (int i = 0; i < static_cast<int>(m_cntItem); i++)
        if (!m_lstItem[i]->m_fillState)
            return false;

    return true;
}

// Fill item in the current order that corresponds to the Item passed into the function
void CustomerOrder::fillItem(Item& item, std::ostream& os)
{
    for (int i = 0; i < static_cast<int>(m_cntItem); i++)
    {
        if (m_lstItem[i]->m_itemName == item.getName()) 
        {
            if (item.getQuantity() > 0) 
            {
                m_lstItem[i]->m_serialNumber = item.getSerialNumber();
                item.updateQuantity();
                m_lstItem[i]->m_fillState = true;
                os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]";
            } 
            else
                os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]";
            
            os << std::endl;
        }
    }
}

void CustomerOrder::display(std::ostream& os) const
{
    os << m_name << " - " << m_product << std::endl;

    for(int i = 0; i < static_cast<int>(m_cntItem); i++)
    {
        os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] " 
        << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName
        << " - " << (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING") << std::endl;
    }
}
