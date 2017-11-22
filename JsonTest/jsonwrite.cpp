//-----------------
//jsonwrite.cpp

#include "jsonwrite.hpp"

void JsonWrite::Indent()
{
    for (int i = 0, s = initialIndentDepth + depth.size(); i < s ; ++i)
    {
        Write() << indent;
    }
}

void JsonWrite::StartContainer (ContainerType type, ContainerLayout layout)
{
    if (forceDefaultContainerLayout)
    {
        layout = defaultContainerLayout;
    } else if(layout == CONTAINER_LAYOUT_INHERIT)
    {
        if (depth.size() > 0)
        {
            layout = depth.top()->layout;

        } else
        {
            layout = defaultContainerLayout;
        }
    }

    StartChild();
    depth.push(new Container(type, layout));
    Write() << (type == CONTAINER_TYPE_OBJECT ? '{' : '[');

}

void JsonWrite::EndContainer()
{
    Container *container = depth.top();
    depth.pop();

    if (container->childCount > 0)
    {
        if (container->layout == CONTAINER_LAYOUT_MULTI_LINE)
        {
            Write() << std::endl;
            Indent();
        } else
        {
            Write() << containerPadding;
        }
    }

    Write() << (container->type == CONTAINER_TYPE_OBJECT ? '}' : ']');

    delete container;

}

void JsonWrite::StartChild(bool isKey)
{
    if (depth.size() == 0)
    {
        if (initialIndentDepth > 0)
        {
            Indent ();

        }
        return;
    }

    Container *container = depth.top();
    if (container->childCount > 0 && (container->type == CONTAINER_TYPE_ARRAY || (container ->type == CONTAINER_TYPE_OBJECT && !container->isKey)))
    {
        Write() << ",";

        if (container -> layout == CONTAINER_LAYOUT_SINGLE_LINE)
        {
            
            Write() << containerPadding;

        } else
        {
            Write() << std::endl;
            Indent();
        }
    } else if (container->childCount == 0)
    {
        Write() << containerPadding;
        if (container->layout == CONTAINER_LAYOUT_MULTI_LINE )
        {
            Write() << std::endl;
            Indent();
        }
    }
    container->isKey = isKey;
    container->childCount++;
}

void JsonWrite::WriteString(const char *str)
{
    Write() << "\"";
    for (int i = 0; str[i] != 0; ++i)
    {
        WriteEscapeChar (str[i]);
    }
    Write () << "\"";
}

void JsonWrite::WriteEscapeChar(char c)
{
    switch(c)
    {
        case '"':  Write() << "\\\""; break;
        case '\\': Write() << "\\\\"; break;
        case '\b': Write() << "\\b"; break;
        case '\f': Write() << "\\f"; break;
        case '\n': Write() << "\\n"; break;
        case '\r': Write() << "\\r"; break;
        case '\t': Write() << "\\t"; break;
        default: Write() << c; break;

    }
}

void JsonWrite::Value(const char *value)
{
    StartChild();
    WriteString(value);
}

void JsonWrite::Value(std::string value)
{
    StartChild();
    WriteString(value.c_str());
}

void JsonWrite::Value(bool value)
{
    StartChild();
    Write() <<(value ? "true" : "false");
}

void JsonWrite::Key(const char *key)
{
    StartChild(true);
    WriteString(key);
    Write() << keyPaddingLeft << ":" << keyPaddingRight;
}

void JsonWrite::NullValue()
{
    StartChild();
    Write() << "null";
}


















