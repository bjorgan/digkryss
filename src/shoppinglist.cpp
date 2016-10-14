#include "shoppinglist.h"

ShoppingList::ShoppingList(QObject *parent) : QAbstractTableModel(parent)
{
}

void ShoppingList::newItem(QString itemName, double price, int amount)
{
	//TODO: call correct rowChanged, rowInserted functions. 

	setItemPrice(itemName, price);
	setItemAmount(itemName, amount);
}

void ShoppingList::setItemPrice(QString itemName, double price)
{
	if (price > 0) {
		items[itemName].second = price;
	}
}

void ShoppingList::setItemAmount(QString itemName, int amount)
{
	if (amount > 0) {
		items[itemName].first = amount;
	}
}

void ShoppingList::deleteItem(QString itemName)
{
	items.erase(items.find(itemName));
}

void ShoppingList::wipeList()
{
	items.clear();
}

void ShoppingList::deleteLastAddedItem()
{
}

double ShoppingList::getTotalAmount()
{
}

/**
 * QAbstractTableModel subclassing convenience functions.
 **/

void ShoppingList::setItemAmount(const QModelIndex &parent, int amount)
{
	setItemAmount(getItem(parent).key(), amount);
}

void ShoppingList::deleteItem(const QModelIndex &parent)
{
	deleteItem(getItem(parent).key());
}

ShoppingListData::const_iterator ShoppingList::getItem(const QModelIndex &parent) const
{
	return (items.begin() + parent.row());
}

ShoppingListData::iterator ShoppingList::getItem(const QModelIndex &parent)
{
	return (items.begin() + parent.row());
}

/**
 * Neccessary functions for QAbstractTableModel subclassing.
 **/

int ShoppingList::rowCount(const QModelIndex &parent) const
{
	return items.size();
}

int ShoppingList::columnCount(const QModelIndex &parent) const
{
	return NUM_SHOPPINGLIST_PROPERTIES;
}

QVariant ShoppingList::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole) {
		ShoppingListData::const_iterator item = getItem(index);
		int column = index.column();

		switch (column) {
			case ITEM_NAME_COL:
				return QVariant(item.key());
			case ITEM_PRICE_COL:
				return QVariant(item->second);
			case ITEM_AMOUNT_COL:
				return QVariant(item->first);
		}
	}

	return QVariant(QVariant::Invalid);
}

Qt::ItemFlags ShoppingList::flags(const QModelIndex &index) const
{
	if (index.column() == ITEM_AMOUNT_COL) {
		return Qt::ItemIsEnabled | Qt::ItemIsEditable;
	} else {
		return Qt::NoItemFlags;
	}
}

/**
 * QAbstractTableModel edit functions.
 **/

bool ShoppingList::setData(const QModelIndex &index, const QVariant &value, int role)
{
	ShoppingListData::iterator item = getItem(index);
	if (index.column() == ITEM_AMOUNT_COL) {
		setItemAmount(item.key(), value.toInt());
		emit dataChanged(index, index);
		return true;
	}

	return false;
}
