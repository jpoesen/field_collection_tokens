Field collection Tokens
=======================

This module allows administrators to define custom tokens for any field_collection
fields on their nodes.

The 'token' display mode is used for rendering subsituted field_collection fields. 
Rendering falls back to 'default' display mode if 'token' mode is not used.

Best used together with token_filter so users can use tokens in textareas
to target field_collection values.

**Dependencies:**

* token
* field_collection

Recommended:

* token_filter

**Configuration:**

On admin/structure/field-collections/tokens, a token field is available for
every defined field_collection field. Just add custom token names and save.

**Example scenario:**

* field_example is a field_collection field, added to node type Article
* token_filter is installed and 'substitute tokens' is added to 'full_html' input type
* on admin/structure/field-collections/tokens, filter [example] is defined for 'field_example'
* on an Article node, filter [example:1] is added to the body
* on an Article node, filter [example:2] is added to the body
* on an Article node, filter [example:all] is added to the body

Result:

When the article is displayed, the first two tokens will be replaced by the example
field_collection's first and second values. The third token will be replaced by
all the values.


**Implementation:**
 Warning: we deviate from the standard way tokens are supposed to be used.
 As a result, this is probably a bit of a hairy implementation: rather than
 following the [type:token] pattern, we're using [token:delta].

 Since the point of this module is to allow users to define their own tokens
 and not restrict them to [foo:token].

 This has the disadvantage if a custom token name such as [node:1] or [user:all]
 is chosen, things can become unpredictable. This is being addressed.
