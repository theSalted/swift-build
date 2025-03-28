//===----------------------------------------------------------------------===//
//
// This source file is part of the Swift open source project
//
// Copyright (c) 2025 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_C_CAS_PLUGINAPI_TYPES_H
#define LLVM_C_CAS_PLUGINAPI_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define LLCAS_VERSION_MAJOR 0
#define LLCAS_VERSION_MINOR 1

typedef struct llcas_cas_options_s *llcas_cas_options_t;
typedef struct llcas_cas_s *llcas_cas_t;
typedef struct llcas_cancellable_s *llcas_cancellable_t;

/**
 * Digest hash bytes.
 */
typedef struct {
  const uint8_t *data;
  size_t size;
} llcas_digest_t;

/**
 * Data buffer for stored CAS objects.
 */
typedef struct {
  const void *data;
  size_t size;
} llcas_data_t;

/**
 * Identifier for a CAS object.
 */
typedef struct {
  uint64_t opaque;
} llcas_objectid_t;

/**
 * A loaded CAS object.
 */
typedef struct {
  uint64_t opaque;
} llcas_loaded_object_t;

/**
 * Object references for a CAS object.
 */
typedef struct {
  uint64_t opaque_b;
  uint64_t opaque_e;
} llcas_object_refs_t;

/**
 * Return values for a load operation.
 */
typedef enum {
  /**
   * The object was found.
   */
  LLCAS_LOOKUP_RESULT_SUCCESS = 0,

  /**
   * The object was not found.
   */
  LLCAS_LOOKUP_RESULT_NOTFOUND = 1,

  /**
   * An error occurred.
   */
  LLCAS_LOOKUP_RESULT_ERROR = 2,
} llcas_lookup_result_t;

/**
 * Callback for \c llcas_cas_load_object_async.
 *
 * \param ctx pointer passed through from the \c llcas_cas_load_object_async
 * call.
 * \param error message if an error occurred. If set, the memory it points to
 * needs to be released via \c llcas_string_dispose.
 */
typedef void (*llcas_cas_load_object_cb)(void *ctx, llcas_lookup_result_t,
                                         llcas_loaded_object_t, char *error);

/**
 * Callback for \c llcas_actioncache_get_for_digest_async.
 *
 * \param ctx pointer passed through from the
 * \c llcas_actioncache_get_for_digest_async call.
 * \param error message if an error occurred. If set, the memory it points to
 * needs to be released via \c llcas_string_dispose.
 */
typedef void (*llcas_actioncache_get_cb)(void *ctx, llcas_lookup_result_t,
                                         llcas_objectid_t, char *error);

/**
 * Callback for \c llcas_actioncache_put_for_digest_async.
 *
 * \param ctx pointer passed through from the
 * \c llcas_actioncache_put_for_digest_async call.
 * \param error message if an error occurred. If set, the memory it points to
 * needs to be released via \c llcas_string_dispose.
 */
typedef void (*llcas_actioncache_put_cb)(void *ctx, bool failed, char *error);

#endif /* LLVM_C_CAS_PLUGINAPI_TYPES_H */
